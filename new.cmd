@echo off
if "%1"=="" goto usage
hugo new posts/%1.md
cat public\tags\index.xml | grep "guid" | sed "s/.*tags\/\([a-z]\+\).*/\1/" | "\Program Files\Git\usr\bin\sort.exe" | paste -s -d" " - | sed -e "s/ /\", \"/g" -e "s/^/[ \"/" -e "s/$/\" ]/" >> content\posts\%1.md
unix2dos content\posts\%1.md
gvim content\posts\%1.md
goto :eof

:usage
echo How to use: new [slug]
