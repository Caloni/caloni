rem @echo off
hugo --buildDrafts --theme=book -d book
pushd book
sed -i "s/href=\"\//href=\"#/g" index.html
sed -i "s/href=\"#[a-z]\+\/[a-z.-]\+/href=\"#/g" index.html
kindlegen.exe book.opf -o caloni.mobi
if exist k:\ cp caloni.mobi k:\documents
popd
