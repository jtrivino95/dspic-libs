.equ COUNTS_10US,  0x0063       ; 99 * 3 / (7372800*4) = 10us
.equ COUNTS_20US,  0x00C6       ; 198 * 3 / (7372800*4) = 20us
.equ COUNTS_150US, 0x05C2       ; 1474 * 3 / (7372800*4) = 150us
.equ COUNTS_5MS ,  0xC000       ; 49152 * 3 / (7372800*4) = 5ms

.section  .text
          .global   _Delay10us
          .global   _Delay20us
          .global   _Delay150us
          .global   _Delay5ms
          .global   _Delay15ms
          .global   _Delay3Tcy

_Delay3Tcy:
.macro Delay3Tcy value:
    mov    \value, W1
    dec    W1, W1
    bra    NZ, $-2
.endm
    return

_Delay10us:
    Delay3Tcy #COUNTS_10US
    return
_Delay20us:
    Delay3Tcy #COUNTS_20US
    return
_Delay150us:
    Delay3Tcy #COUNTS_150US
    return
_Delay5ms:
    Delay3Tcy #COUNTS_5MS
    return
_Delay15ms:
    Delay3Tcy #COUNTS_5MS
    Delay3Tcy #COUNTS_5MS
    Delay3Tcy #COUNTS_5MS
    return

    .end
