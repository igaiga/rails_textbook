# https://igaiga.esa.io/posts/1566
# Re:VIEW Starter
# https://kauplan.org/reviewstarter/
# $ docker pull kauplan/review2.5 # 3GB 以上ダウンロードするので注意
# $ unzip mybook.zip # webから設定していくとできあがる
# $ cd mybook/
# $ docker run --rm -v $PWD:/work kauplan/review2.5 /bin/bash -c "cd /work; rake pdf"

docker run --rm -v $PWD:/work kauplan/review2.5 /bin/bash -c "cd /work; rake pdf"
open mybook.pdf
