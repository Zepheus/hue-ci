# BitBucket Pipelines configuration

Add the following files to your repository (at root level):
- bootstrap.sh
- build.sh
- publish-build-status.sh
- bitbucket-pipelines.yml

The current configuration is based on top of DotNet Core, but other base images can be used as well. Change `build.sh` accordingly.

## Configuration
1. Change your App secret, obtained from your FireBase configuration and project URL in `publish-build-status.sh`.
1. Change `RESOURCE` to your repository name
1. Enable Bitbucket Pipelines in your BitBucket configuration panel

## Migrating existing BitBucket Pipelines
To migrate your existing script configuration, place all of your `script` commands into `build.sh` and use the `bitbucket-pipelines.yml` from above.
It will be automatically bootstrapped.