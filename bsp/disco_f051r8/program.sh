#! /bin/bash -eu

# program.sh
# PUBLIC DOMAIN
# https://www.purposeful.co.uk/goodmicro/


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

set +e
trap 'echo "this script must be executed not sourced" >&2' RETURN
return 1 2>/dev/null
trap - RETURN
set -eu

this_script="$(readlink -ve "$BASH_SOURCE")"
this_script_dir="$(dirname "$this_script")"
this_script_name="$(basename "$this_script")"

if [ $# -ne 1 ]
then
  echo Usage: $this_script_name FILE.hex >&2
  exit 1
fi

hex="$(readlink -ven "$1")"

for winprog in "/cygdrive/c/Program Files/STMicroelectronics/STM32 ST-LINK Utility/ST-LINK Utility/ST-LINK_CLI.exe" "/cygdrive/c/Program Files (x86)/STMicroelectronics/STM32 ST-LINK Utility/ST-LINK Utility/ST-LINK_CLI.exe"
do
  if [ -x "$winprog" ]
  then
    exec "$winprog" -c SWD FREQ=1000 UR -P "$hex" -V -HardRst
  fi
done

for d in /usr/local/STMicroelectronics/STM32Cube/STM32CubeProgrammer /opt/st/stm32cubeide_*/plugins/com.st.stm32cube.ide.mcu.externaltools.cubeprogrammer.*/tools /c/ST/STM32CubeIDE*/STM32CubeIDE/plugins/com.st.stm32cube.ide.mcu.externaltools.cubeprogrammer.*/tools
do
  if [ -x "$d/bin/STM32_Programmer_CLI" ]
  then
    LD_LIBRARY_PATH="$d/lib${LD_LIBRARY_PATH:+:}${LD_LIBRARY_PATH-}" exec "$d/bin/STM32_Programmer_CLI" --connect port=SWD freq=1000 reset=HWrst mode=UR --write "$hex" --verify -hardRst -run
  fi
done

if ! which openocd >/dev/null
then
  echo $this_script_name: neither STM32_Programmer_CLI nor openocd installed >&2
  exit 1
fi

exec openocd -f "$this_script_dir/stm32f0discovery.cfg" -c "program \"$hex\" verify reset exit"
