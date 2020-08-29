rem @echo off
copy /y layouts\book.html layouts\index.html
hugo --buildDrafts
git checkout layouts\index.html
pushd public\book
move /y ..\index.html .
kindlegen.exe book.opf -o caloni.mobi
if exist k:\ cp caloni.mobi k:\documents
popd
