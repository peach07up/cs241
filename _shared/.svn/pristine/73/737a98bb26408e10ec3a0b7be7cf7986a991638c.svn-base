#!/usr/bin/perl
#
# Run this as follows:
# ./19-quantum > /tmp/trace.txt   # run for a while, e.g. a minute
# ./count_lines.pl < /tmp/trace.txt
#
# Let it run for a while, long enough to get some statistics
# (a minute or so is probably OK).
#
# This program counts the number of lines printed by each thread in its quantum,
# before switching to the other thread. This data can then be plotted by gnuplot.

$last_line = '';
$count = 0;

%count_counts = ();
$num_quanta = 0;

while ($line = <>) {
    if ($line eq $last_line) {
        $count++;
    }
    else {
        if ($count > 0) {
            # We now have a data point: there were $count printfs in the quantum.
            unless ($count_counts{$count}) {
                $count_counts{$count} = 0;
            }
            $count_counts{$count}++;
            $num_quanta++;
        }
        $count = 1;
    }
    $last_line = $line;
}

@sorted_keys = sort {$a <=> $b} (keys %count_counts);
$last_count = $sorted_keys[0] - 1;
foreach $count (@sorted_keys) {
    $fraction = $count_counts{$count} / $num_quanta;
    if ($count != $last_count + 1) {
        printf "\n"; # so we get a blank line so gnuplot does not connect the lines
    }
    $last_count = $count;
    printf "$count $count_counts{$count} $fraction\n";
}