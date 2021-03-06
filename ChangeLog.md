# ProbeAPI Tools History (ChangeLog)

## Next version


## Version 1.4.34 (12 September 2016)

* moved from Mashape to Kong


## Version 1.4.33 (19 August 2015)

* minor changes in error messages
* Changed default values in dping:
  * single ping timeout: 3000ms -> 1000ms
  * wait time for server response: 2000ms -> 4000ms
* Changed default values in dtracert:
  * wait time for server response: 2000ms -> 4000ms


## Version 1.4.32 (27 July 2015)

* added command line options for dtracert:
  * -hs hop_number  First hop number to start from.


## Version 1.4.30 (29 June 2015)

* updated code to use and parse latest web API changes: more command line options, more control and etc.
* added command line options for both dping and dtracert:
  * -l size         - Send buffer size.
  * -f              - Set Don't Fragment flag in packet (IPv4-only).
  * -4              - Force using IPv4.
  * -6              - Force using IPv6.
  * --api-key key   - Set web API key.
  * --api-url url   - Set web API URL.
* added command line options for dping: -t, -a, -np, -i
  * -t              - Ping the specified host until stopped. To see statistics and continue - type Control-Break; To stop - type Control-C.
  * -a              - Resolve addresses to hostnames.
  * -np count       - Number of pings per probe to send (default: 1).
  * -i TTL          - Time To Live.
* added command line options for dtracert:
  * -d              - Do not resolve addresses to hostnames.
  * -hf max_hops    - Maximum number of failed hops in a row to stop (default: 3).
* changed default dping TTL from 128 to 55 (like in Windows 8)
* Changed default values in dping:
  * single ping timeout: 5000 ms -> 3000 ms
  * pings per probe: 3 -> 1
  * wait between pings: 1000ms -> 100 ms
  * TTL: 128 -> 55
  * total time for API call: 5000ms (unchanged)
  * probe count: 10 (unchanged)
* Changed default values in dtracert:
  * single ping timeout: 3000 ms -> 1000 ms
  * wait between pings: 1000ms -> 100 ms
  * total time for API call: 44 sec -> 47 sec
  * probe count: 40 (default 10 * factor 4) -> 10
* fixed bug with delays during dtraceroute print. Printing is much faster now
* don't exit if Control+Break is catched during dping. Print statistics and continue (like Windows ping does)
* allow target host to be specified at any position of command line (not necessary to have it at the end of command line any more)
* added --probes command line switch as an alias for -n (both dping and dtracert)
* other fixes


## Version 1.3.28 (6 June 2015)

* added --no-delays command line option
* use zlib for cURL in Windows
* Minor bugs fixed
* added cmake scripts for crossplatform building
* supported compilation environments:
  * native MSVC
  * cmake: auto-generated MSVC
  * cmake: MinGW for Windows + makefiles + gcc
  * cmake: Unix makefiles + gcc in Linux
* use submodules in git to get dependent sources
* redistribute pre-built RPM packet for linux


## Version 1.1.22 (22 May 2015)

* fixed a bug in dping which caused skipping of final statistics print
* documentation is generated automatically now
* other code improvements

**WARNING!** dtraceroute's --asn mode is broken in this release!

 
## Version 1.1.20 (21 May 2015)

* dtraceroute project is implemented
* program termination is now more correct
* source code was deduplicated


## Version 1.0.16 (18 May 2015)

* Added license, copyrights, documentation.
* Disabled default mode which caused pinging from country with most of endpoints online.
* Smaller curl runtime (excluded unused protocols).


## Version 1.0.13 (13 May 2015)

All dping utility features from wiki are implemented:

* --list-country - List available countries.
* --list-asn {code} - List available ASNs for specified country code (ISO 3166-1 alpha-2).
* --country {code} - Ping from specified 2 letter country code (ISO 3166-1 alpha-2).
* --asn {id} - Ping from specified ASN.

Usage examples:
* dping --asn AS12357 8.8.8.8
* dping --country US 8.8.8.8


## Version 0.5.7 (11 May 2015)

dping utility got its first few features implemented.

It currently allows two main command line modes:

* --list-country - List available countries.
* --country {code} - Ping from specified 2 letter country code (ISO 3166-1 alpha-2).
