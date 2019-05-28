[build-menu]
FT_00_LB=_Compile
FT_00_CM=gcc -Wall -Wcpp -std=c99 -Wcpp  -c "%f"
FT_00_WD=
FT_02_LB=_Lint
FT_02_CM=cppcheck --language=c --enable=warning,style --template=gcc "%f"
FT_02_WD=
