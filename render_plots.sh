writeplot() {
    printf "Rendering %s\n" $1
    rntcairo plotter.rnt $1.rnt $1.png 
}

make mkplots
./mkplots

writeplot line_1
writeplot line_2
writeplot line_3
writeplot line_4
writeplot line_5
writeplot line_6
writeplot line_7
