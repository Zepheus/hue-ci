#!/bin/bash
APP_SECRET="XXX"  # Firebase app secret
RESOURCE="https://XXX.firebaseio.com/build-status/dotnet-test.json"

if [ "$1" -eq "0" ]; then
    PAYLOAD='{ "success": true }'
else
    PAYLOAD='{ "success": false }'
fi
curl -X PUT -d "${PAYLOAD}" -H "Content-Type:application/json" "${RESOURCE}?auth=${APP_SECRET}"