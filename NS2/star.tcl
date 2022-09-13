set ns [new Simulator]
set nf [open out.nam w]

$ns namtrace-all $nf
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]

$ns duplex-link $n0 $n1 1Mb 10ms DropTail
$ns duplex-link $n0 $n2 1Mb 10ms DropTail
$ns duplex-link $n0 $n3 1Mb 50ms DropTail
$ns duplex-link $n0 $n4 1Mb 50ms DropTail

set udp0 [new Agent/UDP]
$ns attach-agent $n0 $udp0
set udp1 [new Agent/UDP]
$ns attach-agent $n1 $udp1
set udp2 [new Agent/UDP]
$ns attach-agent $n2 $udp2
set udp3 [new Agent/UDP]
$ns attach-agent $n3 $udp3
set udp4 [new Agent/UDP]
$ns attach-agent $n4 $udp4

set cbr0 [new Application/Traffic/CBR]
$cbr0 set packetSize_ 500
$cbr0 set internal_ 1
$cbr0 attach-agent $udp0 
set cbr1 [new Application/Traffic/CBR]
$cbr1 set packetSize_ 500
$cbr1 set internal_ 1
$cbr1 attach-agent $udp1
set cbr2 [new Application/Traffic/CBR]
$cbr2 set packetSize_ 500
$cbr2 set internal_ 1
$cbr2 attach-agent $udp2 
set cbr3 [new Application/Traffic/CBR]
$cbr3 set packetSize_ 500
$cbr3 set internal_ 1
$cbr3 attach-agent $udp3
set cbr4 [new Application/Traffic/CBR]
$cbr4 set packetSize_ 500
$cbr4 set internal_ 1
$cbr4 attach-agent $udp4

set null0 [new Agent/Null]
$ns attach-agent $n0 $null0
$ns connect $udp1 $null0
set null1 [new Agent/Null]
$ns attach-agent $n1 $null1
$ns connect $udp2 $null1
set null2 [new Agent/Null]
$ns attach-agent $n2 $null2
$ns connect $udp3 $null2  
set null3 [new Agent/Null]
$ns attach-agent $n3 $null3
$ns connect $udp4 $null3  
set null4 [new Agent/Null]
$ns attach-agent $n4 $null4
$ns connect $udp0 $null4  

proc finish {} {
	global ns nf
	$ns flush-trace
	close $nf
	exec nam out.nam &
	exit 0
}

$ns at 0.5 "$cbr0 start"
$ns at 4.5 "$cbr0 stop"
$ns at 0.5 "$cbr1 start"
$ns at 4.5 "$cbr1 stop"
$ns at 0.5 "$cbr2 start"
$ns at 4.5 "$cbr2 stop"
$ns at 0.5 "$cbr3 start"
$ns at 4.5 "$cbr3 stop"
$ns at 0.5 "$cbr4 start"
$ns at 4.5 "$cbr4 stop"
$ns at 5.0 "finish"
$ns run 
