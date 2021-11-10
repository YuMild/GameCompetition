# Stubs for _operator (Python 3.5)

from typing import AnyStr

# In reality the import is the other way around, but this way we can keep the operator stub in 2and3
from operator import (
    truth as truth,
    contains as contains,
    indexOf as indexOf,
    countOf as countOf,
    is_ as is_,
    is_not as is_not,
    index as index,
    add as add,
    sub as sub,
    mul as mul,
    floordiv as floordiv,
    truediv as truediv,
    mod as mod,
    neg as neg,
    pos as pos,
    abs as abs,
    inv as inv,
    invert as invert,
    length_hint as length_hint,
    lshift as lshift,
    rshift as rshift,
    not_ as not_,
    and_ as and_,
    xor as xor,
    or_ as or_,
    iadd as iadd,
    isub as isub,
    imul as imul,
    ifloordiv as ifloordiv,
    itruediv as itruediv,
    imod as imod,
    ilshift as ilshift,
    irshift as irshift,
    iand as iand,
    ixor as ixor,
    ior as ior,
    concat as concat,
    iconcat as iconcat,
    getitem as getitem,
    setitem as setitem,
    delitem as delitem,
    pow as pow,
    ipow as ipow,
    eq as eq,
    ne as ne,
    lt as lt,
    le as le,
    gt as gt,
    ge as ge,
    itemgetter as itemgetter,
    attrgetter as attrgetter,
    methodcaller as methodcaller,
    matmul as matmul,
    imatmul as imatmul,
)

def _compare_digest(a: AnyStr, b: AnyStr) -> bool: ...
