rem @echo off
hugo -D --theme book --destination book
pushd book
iconv -f UTF-8 -t LATIN1 index.html > book.html
kindlegen.exe book.opf -o cinetenisverde.mobi
if exist k:\ copy /y cinetenisverde.mobi k:\documents
popd
