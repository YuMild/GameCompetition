/*!
 * @brief	?X?v???C?g?p??V?F?[?_?[?B
 */

cbuffer cb : register(b0){
	float4x4 mvp;		//???[???h?r???[?v???W?F?N?V?????s??B
	float4 mulColor;	//??Z?J???[?B
    float4 screenParam;
    float2 imageParam;
    int isRight = 0;
    int isUp = 0;
};
struct VSInput{
	float4 pos : POSITION;
	float2 uv  : TEXCOORD0;
};

struct PSInput{
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

Texture2D<float4> colorTexture : register(t0);	//?J???[?e?N?X?`???B
sampler Sampler : register(s0);

PSInput VSMain(VSInput In) 
{
	PSInput psIn;
	psIn.pos = mul( mvp, In.pos );
	psIn.uv = In.uv;
	return psIn;
}
float4 PSMain( PSInput In ) : SV_Target0
{
	
    //右側を表示させない。
    if (isRight == 1)
    {
        if (In.pos.x > imageParam.x)
        {
            clip(-1);
        }
    }
    //左側を表示させない。
    else if (isRight == 0)
    {
        if (In.pos.x < imageParam.x)
        {
            clip(-1);
        }
    }
    
    //上側を表示させない。
    if (isUp == 1)
    {
        if (In.pos.y < imageParam.y)
        {
            clip(-1);
        }
    }
    //下側を表示させない。
    else if (isUp == 0)
    {
        if (In.pos.y > imageParam.y)
        {
            clip(-1);
        }
    }
    
    
    float4 color = colorTexture.Sample(Sampler, In.uv) * mulColor;
	return color;
}
float4 PSMainGamma( PSInput In ) : SV_Target0
{
	float4 color = colorTexture.Sample(Sampler, In.uv) * mulColor;
	color.xyz =  pow(max( color.xyz, 0.0001f ), 1.0f/2.2f);
	return color;
}