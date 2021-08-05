# Simple_Player_System
### 一个使用C++实现的简单玩家系统，实现了玩家的登入、注册、升级、登出功能
* 分成多个类进行控制
* User类负责用户数据的保存与修改
8 UserMgr负责管理用户类并与DB类交互
* DB类负责与数据库进行交互
* LoginSystem类负责登入登出的接口，并与UserMgr类交互
* LevelSysrem类负责升级的操作，与UserMgr类交互
