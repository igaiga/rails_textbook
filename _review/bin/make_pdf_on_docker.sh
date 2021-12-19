# Docker上でPDFを作成するスクリプト
# $ bin/make_pdf_on_docker.sh

# Re:VIEW Starter
# iga memo: https://igaiga.esa.io/posts/1566
# https://kauplan.org/reviewstarter/
# DockerHub https://hub.docker.com/r/kauplan/review2.5/
# Docker Image GitHub https://github.com/kauplan/docker-review
# Docker Image GitHub forked https://github.com/igaiga/docker-review
# $ docker pull kauplan/review2.5 # 3GB 以上ダウンロードするので注意
# $ unzip mybook.zip # webから設定していくとできあがる
# $ cd mybook/
# $ docker run --rm -v $PWD:/work kauplan/review2.5 /bin/bash -c "cd /work; rake pdf"

docker run --rm -v $PWD:/work kauplan/review2.5 /bin/bash -c "cd /work; rake pdf"

open mybook.pdf
