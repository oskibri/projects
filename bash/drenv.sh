#!/bin/bash

fullchain=$(cat <<EOF
-----BEGIN CERTIFICATE-----
MIIB1zCCAX2gAwIBAgIUetk/dfIj+XLoTuPXGo9zvpEDuVgwCgYIKoZIzj0EAwIw
RDELMAkGA1UEBhMCTk8xETAPBgNVBAoMCE9za2FyIEFTMRMwEQYDVQQLDApPcGVy
YXRpb25zMQ0wCwYDVQQDDARPSVgxMB4XDTI0MTAxODE4MTk0NVoXDTI3MDcxNDE4
MTk0NVowPTELMAkGA1UEBhMCTk8xDjAMBgNVBAoMBW9za2FyMQ4wDAYDVQQLDAVv
c2thcjEOMAwGA1UEAwwFb3NrYXIwWTATBgcqhkjOPQIBBggqhkjOPQMBBwNCAATc
z1la4k3RiRgiS4xLUZau21kIBT2RFhVJ8d+D3GH5HnSzg1xvYxqOd3V9y9ao7SaN
JFD9G8jMwNa/feZkChW4o1QwUjAQBgNVHREECTAHggVvc2thcjAdBgNVHQ4EFgQU
HeCRT3k42zf10fYdVdgczB8c6KYwHwYDVR0jBBgwFoAUznH3LUYrkMVXXGL9FuCq
b308skswCgYIKoZIzj0EAwIDSAAwRQIhAP5jp/DVLGPD9A5Scfoxbr3cLEdhzk4n
fGurlTk+7OVhAiBjGKbyILQ0A29TJTIkb1vgSxxAOQGfgjfHrNeQ5MTohQ==
-----END CERTIFICATE-----
-----BEGIN CERTIFICATE-----
MIIB9DCCAZqgAwIBAgIUb52coGjFRwi19j/kGtymy57cVc8wCgYIKoZIzj0EAwIw
SzELMAkGA1UEBhMCTk8xETAPBgNVBAoMCE9za2FyIEFTMRMwEQYDVQQLDApPcGVy
YXRpb25zMRQwEgYDVQQDDAtPc2thclJvb3RDQTAeFw0yNDA2MjQwMDI1MjZaFw0z
NDA2MjIwMDI1MjZaMEQxCzAJBgNVBAYTAk5PMREwDwYDVQQKDAhPc2thciBBUzET
MBEGA1UECwwKT3BlcmF0aW9uczENMAsGA1UEAwwET0lYMTBZMBMGByqGSM49AgEG
CCqGSM49AwEHA0IABGb0AK8OFDhQe7hGGQTnxfAfrOGahmcV5Pf37dAKT+2HFz7g
YBX4BFyDN6HkwkA0GXeD8f/gusWUq+akpy3fSs2jYzBhMA8GA1UdEwQIMAYBAf8C
AQAwDgYDVR0PAQH/BAQDAgEGMB0GA1UdDgQWBBTOcfctRiuQxVdcYv0W4KpvfTyy
SzAfBgNVHSMEGDAWgBRmf/DmlpZyE9W+2O37q2P683WW1DAKBggqhkjOPQQDAgNI
ADBFAiEArKFFQo7/qWNJQNhYBh6J8tOSBUEIp0REp2riJesplWUCIFNmY2z25lWw
3AwXTssZ3LpagOBuCZHS8vzybDHsOEvS
-----END CERTIFICATE-----
-----BEGIN PRIVATE KEY-----
MIGHAgEAMBMGByqGSM49AgEGCCqGSM49AwEHBG0wawIBAQQgTd7D+/rQNFJ7W4kC
WqTBGSM52fe5HjeWXXxUTuFh+5KhRANCAATcz1la4k3RiRgiS4xLUZau21kIBT2R
FhVJ8d+D3GH5HnSzg1xvYxqOd3V9y9ao7SaNJFD9G8jMwNa/feZkChW4
-----END PRIVATE KEY-----
EOF
)

cert_file=$(mktemp)
echo "$fullchain" > "$cert_file"

if [ $# -lt 2 ]; then
	echo "usage: $0 <user:pass> <env>"
	rm $cert_file
	exit
fi

user=$(cut -d: -f1 <<< $1)
pass=$(cut -d: -f2 <<< $1)
env=$2

function test_ch() {
	curl -sSf "https://clickhouse.r99.no:8443" -u "$user:$pass" --cert "$cert_file" -d "select env from s8.access where env = '$env' limit 1"
	rm "$cert_file"
	exit
}
#test_ch

logfiles=($(find /var/log/httpd -name "access.log*"))

function query_ch() {
	local start=$1
	local end=$2

	curl -sSf "https://clickhouse.r99.no:8443" -u "$user:$pass" --cert "$cert_file" -d "SELECT count() FROM s8.access WHERE env = '$env' AND dynamic = true AND time between toDateTime('$start') and toDateTime('$end') GROUP BY env"
}

for file in "${logfiles[@]}"; do
        if [[ "$file" == *.gz ]]; then
                server_dr=$(zgrep "$env PHP " "$file" | wc -l) 
                startend_date=$(zgrep "$env PHP " "$file" | sed -n '1p;$p' | awk '{print $4}') 
        else
                server_dr=$(grep "$env PHP " "$file" | wc -l)
                startend_date=$(grep "$env PHP " "$file" | sed -n '1p;$p' | awk '{print $4}') 
        fi

	[[ "$startend_date" == '' ]] && continue

        start_date=$(sed -n '1p' <<< "$startend_date" | tr -d '[' | sed -E 's@([0-9]{2})/([a-zA-Z]{3})/([0-9]{4}):@\1 \2 \3 @' | xargs -I {} date -d "{}" "+%Y-%m-%d %H:%M:%S")
        end_date=$(sed -n '$p' <<< "$startend_date" | tr -d '[' | sed -E 's@([0-9]{2})/([a-zA-Z]{3})/([0-9]{4}):@\1 \2 \3 @' | xargs -I {} date -d "{}" "+%Y-%m-%d %H:%M:%S")
	ch_dr=$(query_ch "$start_date" "$end_date")

	diff=$(echo "(($server_dr - $ch_dr) / $server_dr) * 100" | bc -l)

	printf "%s:\n%-20s \x1b[32m%s\x1b[0m\n%-20s \x1b[32m%s\x1b[0m\n%-20s \x1b[32m%d\x1b[0m\n%-20s \x1b[32m%d\x1b[0m\n%-20s \x1b[32m%.2f%%\x1b[0m\n\n" \
    	"$file" \
    	"Start Date:" "$start_date" \
    	"End Date:" "$end_date" \
    	"Server DR:" "$server_dr" \
    	"Clickhouse DR:" "$ch_dr" "Difference:" $diff
done
rm $cert_file
