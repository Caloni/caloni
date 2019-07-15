rem @echo off
hugo -D --theme book --destination book
pushd book
rem iconv -f UTF-8 -t LATIN1 index.html > book.html
cp index.html book.html
kindlegen.exe book.opf -o caloni.mobi
rem if exist k:\ copy /y caloni.mobi k:\documents
popd
