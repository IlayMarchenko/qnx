#!/bin/bash
source ./config.sh

for filename in ./to_upload/*
do 
    sshpass -p ${target_password} scp $filename ${target_user}@${target_ip}:/home/${target_user}/dlt
    echo "uploaded $filename"
done
echo "deploy.sh completed"
