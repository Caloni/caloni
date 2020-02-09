rem @echo off
copy /y layouts\book.html layouts\index.html
hugo
pushd public
move /y index.html book.html
kindlegen.exe book.opf -o caloni.mobi
if exist k:\ copy /y caloni.mobi k:\documents
popd
git checkout layouts\index.html
