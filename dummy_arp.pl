#!/usr/bin/perl

use warnings;
use strict;

my $me = "\xe6\x0a\xe0\x16\x35\xe1";
my $gw = "\xda\x43\x75\x27\xa6\xc0";

print $me . # eth dst 
      $gw . # eth src
      "\x08\x06" .                 # payload type: ARP
      "\x00\x01" .                 # hw type: ethernet
      "\x08\x00" .                 # proto type: IP 
      "\x06\x04" .                 # hwlen, iplen
      "\x00\x02" .                 # opcode (2 == reply)
      $gw . 					   # sender hw
      "\xc0\xa8\x00\x03" .         # sender IP
      $gw . 					   # target hw
      "\xc0\xa8\x00\x02";          # target IP
