FROM alpine:3.7
LABEL maintainers "M.Montazery <m.montazery@faraazin.ir>"

ENV DIRPATH=/usr/E4MT

WORKDIR $DIRPATH

RUN apk update && apk upgrade && apk add --no-cache bash coreutils qt5-qtbase zlib libxml2
RUN apk add --virtual .build-dependencies --no-cache gcc g++ make cmake qt5-qtbase-dev zlib-dev libxml2-dev git \
	&& mkdir $DIRPATH/tmp \
	&& cd $DIRPATH/tmp \
    && git clone --recursive https://github.com/faraazin/E4MT.git \
    && cd $DIRPATH/tmp/E4MT \
    && qmake-qt5 \
    && make -j \        
    && mv $DIRPATH/tmp/E4MT/out/* $DIRPATH \
    && mv $DIRPATH/tmp/E4MT/scripts/E4MT.server.conf $DIRPATH/bin/E4MT.server.conf \
    && rm -rf $DIRPATH/tmp/ \
	&& apk del .build-dependencies

RUN echo $'#!/bin/sh \n\
cd /usr/E4MT/bin \n\
export LD_LIBRARY_PATH=../lib64 \n\
./E4MT "-c" "E4MT.server.conf"' \
>> $DIRPATH/bin/run.sh

RUN ["chmod", "+x", "/usr/E4MT/bin/run.sh"]

EXPOSE 10000

ENTRYPOINT ["/usr/E4MT/bin/run.sh"]
CMD ["sh"]
