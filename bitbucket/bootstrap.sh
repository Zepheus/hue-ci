#!/bin/bash
bash -e "./build.sh"  # -e flag enables early termination on error
exit_status=$?

bash "./publish-build-status.sh" "${exit_status}" # Publish status
exit ${exit_status}  # Pass the exit status