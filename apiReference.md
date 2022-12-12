# API reference Manual
神之眼L提供了一组用于管理功能的restful API，实现了包含设备信息查询、播放列表更改、文件上传下载等功能。您可以依据该手册进行后台管理界面的二次开发。

The Vision L provides restful APIs for management purpose, implemented functions such as device info query, playlist update, file upload, etc. You may develop your own manage backend referencing this manual.

**注意：所有API主机地址均为神之眼的ipv4地址**

**Note：The host of all APIs are the ipv4 address of the Vision.**

## 基础信息 / Basic Info
### GET /api/v1/info
#### Brief
该函数返回神之眼的基础信息，包含设备名、硬件版本、app版本信息。

This function resurns basic info of Vision, including device name, hardware version, app version, etc.

#### Example
~~~
GET /api/v1/info

RESPONSE:
{
    "device_name": "Vision_f768",
    "app_version": "L0.2.1",
    "hw_version": 1
}

~~~

## 播放列表 / Play List
### GET /api/v1/playlist
#### Brief
该函数返回神之眼当前应用的播放列表。

This function returns the playlist Vision currently using.

#### Example
~~~
GET /api/v1/playlist

RESPONSE:
{
    "files":[
        "S:/Pyro.mjpeg",
        "S:/Hydro.mjpeg",
        "S:/Anemo.mjpeg",
        "S:/Electro.mjpeg",
        "S:/Dendro.mjpeg",
        "S:/Cryo.mjpeg",
        "S:/Geo.mjpeg",
        "S:/Unowned.mjpeg"
    ]
}
~~~

### POST /api/v1/playlist
#### Brief
该函数将更新播放列表。

This function will update the playlist.

#### Param
以JSON格式封装的新播放列表，包含在请求体中。

New playlist in JSON, included in request body.

#### Return
新的播放列表或者下列错误中的一个。

The new playlist or error among table below.

| Description | Code |
| --- | --- |
| JSON deseralization error | -1 |
| Invalid JSON              | -2 |


#### Example
~~~
POST /api/v1/playlist
BODY:
{
    "files":[
        "S:/Pyro.mjpeg",
        "S:/Hydro.mjpeg",
        "S:/Anemo.mjpeg"
    ]
}

RESPONSE:
{
    "files":[
        "S:/Pyro.mjpeg",
        "S:/Hydro.mjpeg",
        "S:/Anemo.mjpeg"
    ]
}
~~~

## 文件管理 / File Management
### GET /api/v1/file
#### Brief
该函数用于下载文件。

This function is for file downloads.

#### Param
path: 文件路径，以url形式传参。需要包含挂载路径。

path: File path, passed in url. Mount point should be included.

#### Response
| Description | Code |
| --- | --- |
| Missing parameter | -1 |
| Parameter too long | -2 |
| Unable to open file | -3 |
| No such volume | -5 |
| File not exist | -6 |
| Failed on sending file | -11 |
| No enough ram to create buffer | -20 |

#### Example
~~~
GET /api/v1/file?path=/s/Geo.mjpeg

RESPONSE:
[Geo.mjpeg]
~~~

### POST /api/v1/file
#### Brief
该函数用于上传文件。

This function is for file uploads.

#### Param
path: 文件路径，以url形式传参。需要包含挂载路径。

path: File path, passed in url. Mount point should be included.

#### Response
| Description | Code |
| --- | --- |
| Success | 0 |
| Missing parameter | -1 |
| Parameter too long | -2 |
| Unable to open file | -3 |
| No such volume | -5 |
| Unable to open (create) file | -8 |
| Failed on receiving file | -9 |
| Failed on writing file | -10 |
| No enough ram to create buffer | -20 |

#### Example
~~~
GET /api/v1/file?path=/s/Geo.mjpeg
BODY:
[Geo.mjpeg]

RESPONSE:
{
    "response": "success",
    "code": 0
}
~~~

### DELETE /api/v1/file
#### Brief
该函数用于删除文件/文件夹。

This function is for file (directory) delection.

#### Param
path: 文件路径，以url形式传参。需要包含挂载路径。

path: File path, passed in url. Mount point should be included.

#### Response
| Description | Code |
| --- | --- |
| Success | 0 |
| Missing parameter | -1 |
| Parameter too long | -2 |
| Error occured deleting files | -4 |
| No such volume | -5 |

#### Example
~~~
DELETE /api/v1/file?path=/s/冰.mjpeg

RESPONSE:
{
    "response": "success",
    "code": 0
}
~~~

### GET /api/v1/file/listdir
#### Brief
该函数用于读取文件夹。

This function is to read directory.

#### Param
path: 文件夹路径，以url形式传参。需要包含挂载路径。

path: Directory path, passed in url. Mount point should be included.

#### Response
JSON封装的文件列表，文件夹以'/'开头。

File list in JSON, directories starts witl '/'.

| Description | Code |
| --- | --- |
| Missing parameter | -1 |
| Parameter too long | -2 |
| Unable to open path | -3 |
| No such volume | -5 |

#### Example
~~~
GET /api/v1/file/listdir?path=/s/

RESPONSE:
{
    "files":[
        "/System Volume Information",
        "Hoyolab.json",
        "hk4e_zh-cn.ttf",
        "/The Vision L",
        "Anemo.mjpeg",
        "Cryo.mjpeg",
        "风.mjpeg",
        "Hoyolab_1.json"
    ]
}
~~~

### POST /api/v1/file/makedir
#### Brief
该函数用于新建文件夹。

This function is to create a directory.

**注意：一次只能创建一级文件夹**

**Note: mkdir could only create one level of directory at once**

#### Param
path: 文件夹路径，以url形式传参。需要包含挂载路径。

path: Directory path, passed in url. Mount point should be included.

#### Return
| Description | Code |
| --- | --- |
| Success | 0 |
| Missing parameter | -1 |
| Parameter too long | -2 |
| No such volume | -5 |
| Path already exists | -7 |
| Unable to create directory | -8 |

#### Example
~~~
POST /api/v1/file/makedir?path=/s/新建文件夹

RESPONSE:
{
    "response": "success",
    "code": 0
}
~~~

## 米游社配置 / Hoyolab Configurations
### GET /api/v1/hoyolab/conf
#### Brief
该函数用于获取当前米游社配置。

This function is to get current Hoyolab configurations.

#### Return
JSON封装的米游社配置，包含角色uid，登陆cookie及设备guid。

Hoyolab configuration packed in JSON, including character uid, cookie for login, and device guid.

#### Example
~~~
GET /api/v1/hoyolab/conf

RESPONSE:
{
    "uid":"012345678",
    "cookie":"HOYOLAB_COOKIE",
    "device_guid":"0123456789abcdef0123456789abcdef"
}
~~~

### POST /api/v1/hoyolab/conf
#### Brief
该函数用于设置米游社配置。

This function is to set Hoyolab configurations.

#### Param
JSON封装的米游社配置，包含角色uid，登陆cookie及设备guid。

**注意：三个配置值均是必填项，API将直接从JSON中读取值并覆盖，不会进行校验**

Hoyolab configuration packed in JSON, including character uid, cookie for login, and device guid.

**Note: All the three values are required, the API does not do any validations, just simply overwrite.**

#### Return
| Description | Code |
| --- | --- |
| success | 0 |
| Error when deserializing json | -1 |
| Invalid JSON | -2 |

#### Example
~~~
POST /api/v1/hoyolab/conf
BODY:
{
    "uid":"012345678",
    "cookie":"HOYOLAB_COOKIE",
    "device_guid":"0123456789abcdef0123456789abcdef"
}

RESPONSE:
{
    "response":"success",
    "code":0
}
~~~

## 设备设置 / Device Settings
### GET /api/v1/setting/auto_bright
#### Brief
该函数用于获取或设置自动亮度开关。

This function is to get or set value of auto brightness.

#### Param
value: 要设置的值，"true"或"false"中的一个。获取值时uri中不要带有查询参数。

value: Value to set, should be one of "true" or "false". DO NOT add any query params when getting this value.

#### Return
当前设置值，或更新后的设置值（若有）。

The current setting value, or the updated setting value (if set a new one).

或者下列错误代码中的一个：

or error among table below:
| Description | Code |
| --- | --- |
| Invalid value | -2 |

#### Example
~~~
GET /api/v1/setting/auto_bright?value=false

RESPONSE:
{
    "setting_autoBright":false
}
~~~

### GET /api/v1/setting/auto_rotate
#### Brief
该函数用于获取或设置自动旋转开关。

This function is to get or set value of auto rotation.

#### Param
value: 要设置的值，"true"或"false"中的一个。获取值时uri中不要带有查询参数。

value: Value to set, should be one of "true" or "false". DO NOT add any query params when getting this value.

#### Return
当前设置值，或更新后的设置值（若有）。

The current setting value, or the updated setting value (if set a new one).

或者下列错误代码中的一个：

or error among table below:
| Description | Code |
| --- | --- |
| Invalid value | -2 |

#### Example
~~~
GET /api/v1/setting/auto_rotate?value=false

RESPONSE:
{
    "setting_useAccel":false
}
~~~