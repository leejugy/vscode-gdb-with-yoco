# wsl 접속시 다음 설정 추가

C:\Users\[사용자 이름]

에 .wslconfig 추가

.wslconfig에 다음 줄을 추가

```.wslconfig
[wsl2]

[experimental]
networkingMode=mirrored
```

---

# yocto 설정

local.conf에 다음 줄을 추가


**local.conf**
```bitbake
IMAGE_INSTALL:append = " gdbserver"
EXTRA_IMAGE_FEATURES:append = " debug-tweaks tools-debug"
```

이후 bash에서 두 동작 수행

**bash**

```bash
bitbake core-image-weston

bitbake core-image-weston -c do_populate_sdk
```

**sdk를 설치**
```bash
your_sdk.sh
```

---

# .vscode 설정하기 - 컴파일 도구 설정

warning 감지를 위한 tasks.json 파일 작성

**tasks.json**

```json
{
	"version": "2.0.0",
	"tasks": [
		{
			"type": "cppbuild",
			"label": "C/C++: arm-poky-linux-gnueabi-gcc 활성 파일 빌드",
			"command": "cd /home/leejunggyun/source/gdb_vscode_test;bash compile.sh",
			"args": [
			],
			"options": {
				"cwd": "${fileDirname}"
			},
			"problemMatcher": [
				"$gcc"
			],
			"group": {
				"kind": "build",
				"isDefault": true
			},
			"detail": "컴파일러: /opt/beaglebone/sysroots/x86_64-pokysdk-linux/usr/bin/arm-poky-linux-gnueabi/arm-poky-linux-gnueabi-gcc"
		}
	]
}
```

이후 vscode에서

ctrl + p

">" 를 입력후

Tasks: Run Build Task 실행 시, gcc가 나타내는 모든 경고를 체크할 수 있음

c/c++ 속성 json 파일 변경, 컴파일러 패스, 인텔리센스 모드랑, 컴파일러 arg 설정

compiler arg는 "~$ source yoursdk_dir/environment-setup-xxx" 파일 실행 후 나오는 $CC의 ARG 중에

sysroot 만 넣어주어도 괜찮음

그리고 컴파일러 위치는 "~$ which $CC"로 찾을 것

**c_cpp_properties.json**

```json
{
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "${workspaceFolder}/**"
            ],
            "defines": [],
            "compilerPath": "/opt/rpi-4.0b/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-gcc",
            "intelliSenseMode": "linux-gcc-arm64",
            "compilerArgs": [
                "--sysroot=/opt/rpi-4.0b/sysroots/cortexa72-poky-linux",
                "-Wformat -Wformat-security -Werror=format-security",
                "-D_FORTIFY_SOURCE=2 ",
                "_FORTIFY_SOURCE"
            ]
        }
    ],
    "version": 4
}
```
---

# .vscode 설정하기 - 원격 gdbserver 접속용 launch.json

1. miDebuggerPath를 적절히 설정, 이 루트는 "~$ source yoursdk_dir/environment-setup-xxx" 실행후 which $GDB로 찾을 수 있음

2. program을 적절히 설정. 빌드한 바이너리 파일의 절대 경로

3. miDebuggerServerAddress gdbserver 접속 주소의 ip와 port를 적절히 설정

4. set sysroot의 sysroot 디렉토리를 적절히 설정

**launch.json**

```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "원격 GDB 디버그 (Remote GDB Debug)",
            "type": "cppdbg",
            "request": "launch",
            "program": "/home/leejunggyun/source/gdb_vscode_test/thread",
            "args": [],
            "stopAtEntry": true,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "miDebuggerPath": "/opt/rpi-4.0b/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-gdb",
            "miDebuggerServerAddress": "2.3.4.6:1234",
            "setupCommands": [
                {
                    "description": "GDB에 대한 자동 서식 지정 사용",
                    "text": "enable-pretty-printing",
                    "ignoreFailures": true
                },
                {
                    "description": "Yocto SDK의 sysroot 설정",
                    "text": "set sysroot /opt/rpi-4.0b/sysroots/cortexa72-poky-linux/",
                    "ignoreFailures": false
                }
            ]
        }
    ]
}
```

---

# 디버깅을 진행할 원격 접속 서버 (타겟 보드)

호스트 pc와 타겟 보드를 랜선 연결 후 다음 명령어 실행

```bash
# 방화벽 1234 포트 열어두기 (윈도우의 경우)
ifconfig eth0 up
ifconfig eth0 2.3.4.6
ifconfig eth0 netmask 255.255.255.0

# 핑 쏴서 연결된지 확인, 안나가면 타겟 pc 방화벽 설정확인
ping 2.3.4.5

gdbserver :1234 ./thread
```

바이너리 파일 이름만 적당히 바꿔주기
