CXX=clang
CFLAGS=-O2 -Xclang -disable-O0-optnone -flto -use-gold-plugin -Wl,-plugin-opt=save-temps
CFLAGS=-flto -use-gold-plugin -Wl,-plugin-opt=save-temps -Xclang -disable-O0-optnone -O0

TARGET=aproflib


aproflib-recursive.bc: aproflib.c
	${CXX} ${CFLAGS} -c aproflib.c -o aproflib-recursive.bc


clean:
	rm -rf *.bc ${TARGET}