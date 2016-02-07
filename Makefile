.PHONY:all

load mk_temp.so

all:
        echo Temporary file: ${mk-temp tmpfile.}


mk_temp.so: mk_temp.c
	${CC} -shared -undefined dynamic_lookup -fPIC $< -o $@
