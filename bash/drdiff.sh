#!/bin/bash

envs=($(getent passwd | cut -d: -f1 | grep -E "[a-z]+_[0-9]+"))
bolts=($(getent group | cut -d: -f1 | grep -E "[a-z]+_[0-9]+"))

cert="/etc/vector/certs/fullchain.pem"
key="/etc/vector/certs/private.key"

percent_arr=()
total=0

for bolt in "${bolts[@]}"; do
    chdr=$(curl "https://clickhouse.r99.no:8443" -sd "select sum(amount) from dr.all where bolt = '$bolt' and time between toDateTime('2024-11-14 00:00:00') and now()" --cert "$cert" --key "$key" -u "sbadmin:D44T00kin")
    
    rawdr=$(cat /kunder/${bolt}/*/logs/AccessLog | awk -F\" '$2 !~ /\.(js|css|jpg|png|gif|jpeg|svg|webp|avif|woff|woff2|ttf|otf|ico|mov|webm|doc|pdf|xls|ppt|docx|pptx|xlsx|swf|mp3|wav|txt|md)/ {print}' | wc -l)
    
    echo -e "Bolt: \x1b[32m$bolt\x1b[0m"
    echo "ClickHouse DR: $chdr"
    echo "Access log DR: $rawdr"
    
    if [[ "$rawdr" -ne 0 ]] || [[ "$chdr" -ne 0 ]]; then
        diff=$(awk -v chdr="$chdr" -v rawdr="$rawdr" 'BEGIN {
            diff = ((chdr - rawdr) / rawdr) * 100
            printf "%.2f", (diff < 0 ? -diff : diff)
        }')
        
        echo "Difference: $diff%"
        
        percent_arr+=("$diff")
    else
        echo "Difference: N/A"
    fi
done

for i in "${percent_arr[@]}"; do
    total=$(awk -v total="$total" -v i="$i" 'BEGIN { print total + i }')
done

total=$(awk -v total="$total" -v num_percent_arr="${#percent_arr[@]}" 'BEGIN { print total / num_percent_arr }')

echo "Average Difference: $total%"
