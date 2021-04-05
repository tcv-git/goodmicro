#! /bin/bash -eu

# stm32cube-extract-vectors.sh
# PUBLIC DOMAIN
# https://www.purposeful.co.uk/software/goodmicro


# I, Tom Vajzovic, am the author of this software and its documentation.
# I permanently abandon all copyright and other intellectual property rights
# in them.
#
# I am fairly certain that the software does what the documentation says it
# does, but I do not guarantee that it does, or that it does what you think it
# should.  I do not guarantee that it will not have undesirable side effects.
#
# If you use, modify or distribute this software then you do so at your own
# risk.  If you do not pass on this warning then you may be responsible for any
# problems encountered by those who obtain the software through you.


# script to extract interrupt vector names from STM32Cube startup assember files
# and generate separate vector assember units and headers


for file in startup_*.s
do
  part="${file#startup_}"
  part="${part%.s}"

  csplit "$file" '%g_pfnVectors:%' '/.weak/' '%%' '{*}' >/dev/null

  sed 's/^\s*\.word\s\+\(\w\+\).*/\1/;t;d' xx00 >vector_names
  rm -f xx00

  count=$(wc -l <vector_names)
  size=$((count * 4))
  align=$(((count <= 32) ? 7 : ((count <= 64) ? 8 : ((count <= 128) ? 9 : ((count <= 256) ? 10 : 11)))))

  exec >"vectors_${part}.s"

  cat <<EOF
@; vectors_${part}.s
@; automaically generated interrupt vector

.syntax  unified

.section .text.Default_Handler, "ax", %progbits
.global  Default_Handler
.type    Default_Handler, %function
.align   2
.thumb_func

Default_Handler:
b .

.size Default_Handler, . - Default_Handler


.section .isr_vector, "a", %progbits
.global  g_pfnVectors
.type    g_pfnVectors, %object
.size    g_pfnVectors, $size
.align   $align

g_pfnVectors:
.word _estack
EOF

  sed '1d;s/^/.word /' vector_names

  echo

  sed '1d;s/^[A-Za-z_].*/.weak &/;t;d' vector_names

  echo

  sed '1d;s/^[A-Za-z_].*/.thumb_set &, Default_Handler/;t;d' vector_names

  macro="VECTORS_${part^^}_H_INCLUDED"

  exec >"vectors_${part}.h"

  cat <<EOF
// vectors_${part}.h
// automaically generated interrupt vector header

#ifndef $macro
#define $macro

#ifdef __cplusplus
extern "C" {
#endif

EOF

  sed '1d;s/^[A-Za-z_].*/void &(void);/;t;d' vector_names

  cat <<EOF

#ifdef __cplusplus
}
#endif

#endif // $macro
EOF

  rm -f vector_names
done
