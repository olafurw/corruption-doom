# OPS-SAT DOOM

### End of the road

The [mission ended](https://www.esa.int/Enabling_Support/Operations/Mission_complete_for_ESA_s_OPS-SAT_flying_laboratory) on the 22nd of May 2024.    
[Here is a link](https://georges.fyi/opssat/opssat-doom-media-coverage/) to the news coverage this project got.

Thank you.

### Overview

Experiment with the European Space Agency (ESA) to run DOOM in Space onboard the [OPS-SAT satellite](https://www.esa.int/Enabling_Support/Operations/OPS-SAT).

### Milestones

#### 2023-12-28 18:16:36 (UTC) — DOOM runs in space on OPS-SAT (initial demo checks).

<div align="center">
  <img src="https://github.com/olafurw/opssat-doom/assets/103783/8b2ece4b-bb92-4694-9655-9debc2569c2e" alt="doom-demo-tests" width="600" />
</div>

Explore the [v1.0 results folder](./results/v1.0/) for more.

#### March 23, 2024 — DOOM runs in space and uses the pictures acquired by the spacecraft's onbard camera as its background images in the gameplay environment.

Images captured by the onboard camera are automatically processed and integrated into the game as custom background scenes. This is achieved by updating the game's WAD file to include the acquired images prior to running DOOM. The WAD update and game execution occur immediately after each image capture, showcasing near real-time snapshots of Earth within the gameplay environment.

<div align="center">
  <table>
    <tr>
      <td><img src="./results/v2.0/20240324114436/run-000001/frame-001920.jpg" /></td>
      <td><img src="./results/v2.0/20240324114436/run-000002/frame-000780.jpg" /></td>
    </tr>
    <tr>
      <td><img src="./results/v2.0/20240324114436/run-000003/frame-001911.jpg" /></td>
      <td><img src="./results/v2.0/20240324114436/run-000009/frame-002320.jpg" /></td>
    </tr>
  </table>
</div>

Explore the [v2.0 results folder](./results/v2.0/) for more.

### Setup

Requires the ops-sat-sepp-ci Docker image:

```bash
git clone https://gitlab.com/esa/NMF/ops-sat-sepp-ci-docker.git
cd ops-sat-sepp-ci-docker
docker build -t sepp-ci:latest .
```

Run the following commands:
- To build: `sudo ./docker-build-32.sh`
- To build and package for spacecraft uplink: `sudo ./docker-ipk-create.sh`

The ipk package will be located in the deploy directory.

For a more manual process from inside the Docker container without mapping volumes:

```bash
sudo docker run -it sepp-ci:latest /bin/bash
```

Then:

```bash
# Clone the repo
cd home/user/
git clone https://github.com/olafurw/opssat-doom.git
cd opssat-doom/

# To install packages and init submodules.
./init-repo.sh

# Source the environment setup script
source /home/user/poky_sdk/environment-setup-cortexa8hf-neon-poky-linux-gnueabi

# Builds deutex, deutex dependencies (libpng and libz), image resample, and DOOM
./build-all-32.sh

# Replaces the doom sky with the given image
# also changes the color palette to fit
# generates a new wad demos/doom-earth.wad
./replace-sky.sh sample.jpeg --use-qemu

# Run DOOM demo files, diffs them and outputs everything to "toGround"
./run-32.sh --use-qemu

# List demo outputs
find toGround -type f

# Package for spacecraft uplink
./ipk-create.sh
ls -larth deploy/
```


### How We Got Here

A vision brewing for 13 years:

- **2011**: [Georges](https://georges.fyi) stumbles on what would become [his favorite SMBC comic](https://www.smbc-comics.com/comic/2011-02-17), thank you [Zach](https://mastodon.social/@ZachWeinersmith)!
- **2020**: Georges joins the [OPS-SAT-1](https://www.esa.int/Enabling_Support/Operations/OPS-SAT) mission control team as a Spacecraft Operations Engineer at the European Space Agency (ESA). Visions of running DOOM on a space computer intensifies.
- **2023**: The reality of a 2024 end-of-mission by atmospheric re-entry starts to hit hard. The spacecraft's impending doom (see what I did there?) is a wake-up call to get serious about running DOOM in space before it's too late.
- **2024**: Georges has been asking around for help with compiling and deploying DOOM for the spacecraft's ARM32 onboard computer but isn't making progress. One night, instead of sleeping, he is trapped doomscrolling (ha!) on Instagram and stumbles on a reel from [Ólafur](https://mastodon.social/@olafurw)'s "Doom on GitHub Actions" talk at NDC TechTown 2023: [_Playing Video Games One Frame at a Time_](https://www.youtube.com/watch?v=Z1Nf8KcG4ro). After sliding into the DM, the rest is history.


<br>
<div align="center">
  <img src="https://www.smbc-comics.com/comics/20110217.gif" alt="Zach Weinersmith SMBC DOOM" width="400" />
</div>

### ASCII Logo

The ASCII art that appears on the spacecraft's eLinux terminal output after installing DOOM is a slightly modified version of the one developed by [Frans P. de Vries (a.k.a. Xymph)](https://doomwiki.org/wiki/Frans_P._de_Vries_(Xymph)). The Spacecraft's terminal outputs get logged and downlinked from space back to the [ESA SMILE ground station](https://www.esa.int/Enabling_Support/Operations/Want_to_SMILE) at ESOC-1 so the ASCII logo is very much noticed and appreciated by the mission control team. A sample log file downlinked from the spacecraft can be found [here](./results/v2.0/20240319183842_78_s_install_exp272_DOOM_sh.log).

```sh
root@sepp:~# opkg install exp272_2.0_sepp_em.ipk
Installing exp272 (2.0) on root
passwd: password expiry information changed.
Configuring exp272.
Installing...

=================     ===============     ===============   ========  ========
\\ . . . . . . .\\   //. . . . . . .\\   //. . . . . . .\\  \\. . .\\// . . //
||. . ._____. . .|| ||. . ._____. . .|| ||. . ._____. . .|| || . . .\/ . . .||
|| . .||   ||. . || || . .||   ||. . || || . .||   ||. . || ||. . . . . . . ||
||. . ||   || . .|| ||. . ||   || . .|| ||. . ||   || . .|| || . | . . . . .||
|| . .||   ||. _-|| ||-_ .||   ||. . || || . .||   ||. _-|| ||-_.|\ . . . . ||
||. . ||   ||-’  || ||  ‘-||   || . .|| ||. . ||   ||-’  || ||  ‘|\_ . .|. .||
|| . _||   ||    || ||    ||   ||_ . || || . _||   ||    || ||   |\ ‘-_/| . ||
||_-’ ||  .|/    || ||    \|.  || ‘-_|| ||_-’ ||  .|/    || ||   | \  / |-_.||
||    ||_-’      || ||      ‘-_||    || ||    ||_-’      || ||   | \  / |  ‘||
||    ‘’         || ||         ‘’    || ||    ‘’         || ||   | \  / |   ||
||            .===’ ‘===.         .===’.‘===.         .===’ /==. |  \/  |   ||
||         .==’   \_|-_ ‘===. .===’   _|_   ‘===. .===’ _-|/   ‘==  \/  |   ||
||      .==’    _-’    ‘-_  ‘=’    _-’   ‘-_    ‘=’  _-’   ‘-_  /|  \/  |   ||
||   .==’    _-’          ‘-__\._-’         ‘-_./__-’         ‘’ |. /|  |   ||
||.==’    _-’                                                     ‘’ |  /==.||
==’    _-’                                                            \/   ‘==
\   _-’                                                                ‘-_   /
 ‘’’                                                                      ‘‘’
```


### Source Ports

Based on [doomgeneric](https://github.com/ozkl/doomgeneric).
