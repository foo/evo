program = ../src/evo.e
brute_force = ../src/brute.e
in = ../in

# here specify tests
# note: up to 3 graphs in one image
# more than one graph is created using ./joinN.sh script (same amount
# of rows needed)

004.res: $(in)/004.in
	$(program) -e avg -i 500 < $< > $@

005.res: $(in)/005.in
	$(program) -e best -i 500 < $< > $@

006a.res: $(in)/006.in
	$(program) -e avg -i 1000 -x pmx < $< > $@

006b.res: $(in)/006.in
	$(program) -e avg -i 1000 -x ox < $< > $@

006c.res: $(in)/006.in
	$(program) -e avg -i 1000 -x cx < $< > $@

006.res: 006a.res 006b.res 006c.res
	./joinN.sh 006a.res 006b.res 006c.res > $@

008.res: $(in)/008.in
	$(program) -v -i 100 -x pmx < $< > $@

001ao.res: $(in)/001.in
	$(brute_force) -e -i 10000 < $< > $@

001bo.res: $(in)/001.in
	$(program) -e avg -i 500 < $< > $@

001o.res: 001ao.res 001bo.res
	./joinN.sh 001ao.res 001bo.res > $@

001h.res: $(in)/001.in
	$(program) -c -i 500 < $< > $@

# here list tests which will be converted into graphs

graphs = 004.pdf 005.pdf 006.pdf 008.pdf

# same as above + optimum line

graphsopt = 001o.pdf 002o.pdf

histos = 001h.pdf

# internals of automatic graph creation

graphs: $(graphs) $(graphsopt) $(histos)

%h.pdf: %h.res
	./plot_histogram.sh $< $@

%o.pdf: %o.res
	./plot_graph_optimum.sh $< $@

gnuplot = graph1.gnuplot graph2.gnuplot graph3.gnuplot
%.pdf: %.res $(gnuplot)
	./plot_graph.sh $< $@


# compilation of presentation

presentation: presentation.pdf
all: presentation.pdf
presentation.pdf: presentation.tex $(graphs)
	pdflatex presentation.tex

# clearing part

clear_presentation:
	rm -f presentation.pdf
	rm -f presentation.aux
	rm -f presentation.log
	rm -f presentation.nav
	rm -f presentation.out
	rm -f presentation.snm
	rm -f presentation.toc

clear_graphs:
	rm -f $(graphs) $(graphsopt)
clear_tests:
	rm -f *.res

clear: clear_tests clear_graphs clear_presentation

# helper for setting execution permission

used_scripts = *.sh
script_permissions:
	chmod +x $(used_scripts)

report: report.pdf
report.pdf: report.tex
	pdflatex report.tex
