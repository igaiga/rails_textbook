# $ bin/copy_imaegs.sh
# ReVIEWで必要な画像ファイルをimagesフォルダへコピー
rm -rf images
cp -r ../assets/ images
cp ../_figures/covers/*.png images/.
cp ../_figures/covers/*.pdf images/.

mv images/smallest-app images/02_smallest_app
mv images/crud images/03_crud
mv images/new-create images/04_new_create
mv images/model images/05_model
mv images/picture-upload images/07_picture_upload
