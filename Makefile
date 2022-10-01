treemap_test: 
	gcc test/lib/treemap_test.c lib/treemap.c -I ./lib/ -o build/treemap_insertion && ./build/treemap_insertion