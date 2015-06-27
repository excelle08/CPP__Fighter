# Fighter C++实验报告

## 程序说明
### 目标用户
单人游戏。用来在空闲时间放松心情。

### 特性
1. 普通模式
2. 无敌模式：此模式下不会因为生命值降为0而GAME OVER

### 游戏规则
#### 1. 怎么移动飞机
使用方向键即可移动飞机。移动速度将随等级升高而加快。

#### 2. 怎样发射炮弹
按空格键发射蓝色炮弹。炮弹的发射频率是有限的，等级越高，允许发射的频率越快

注意：每发出一个炮弹将会消耗5分
#### 3. 敌机
敌机将随机出现并向下飞行，并且生成的数量和飞行速度将随等级升高而增大。

Level 2以后敌机将随机发射红色炮弹。Level 6之前炮弹向下运动，之后它的初速度将指向飞机。炮弹的发射速度也会随等级升高加快。

Level 3以后每隔一段时间将出现一个超大敌机，会发射多发炮弹。

普通敌机一个炮弹即可打爆，每个获得20分；超大敌机存在20个生命值，归零后才会彻底爆炸，每个250分。

没打着而飞出窗口的普通敌机将扣除5分。
#### 4. 生命值
游戏开始初始有50个生命值，每被敌机的炮弹击中一次即扣除5点。在普通模式下生命值归零游戏则结束。

每隔一段时间将生成一个旋转的奖品，击中即可获得5点生命值。
#### 5. 分数与等级
每得500分升高一个等级，但如果扣分到不足以维持该等级将会降级。

游戏难度随等级升高。

分数变为0后无法发射炮弹，游戏即结束。
#### 5. 其他
按等号关闭背景音乐，按0关掉音效，按9恢复。

## 程序结构
### 开发环境
操作系统: `OS X 10.10.3`

编译器: `Apple LLVM version 6.1.0 (clang-602.0.53)`

图形库: `SFML 2.3`

开发工具: `Sublime Text 2`

### 如何编译？
#### 安装依赖库
1. 在官方网站(sfml-dev.org)下载与操作系统与编译器对应的SFML图形库（对于本环境则是Mac OS X）
2. 将必要的文件复制到环境变量所配置的库目录下。
3. 如果你使用Codeblocks, Visual Studio等IDE，你需要根据官方网站的教程来配置图形库

#### 编译
如果使用IDE，则可以直接编译运行，下面说明如何在终端下编译：

首先，需要编写Makefile：(已包含在仓库中)
```
CC=g++
CFLAGS_MAKE=-framework sfml-window -framework sfml-graphics -framework sfml-system -framework sfml-audio -std=c++11 -O3  
CFLAGS_COMPLIE=-std=c++11 -g -O2
  
# 目标文件  
TARGET=main 
SRCS = main.cpp bomb.cpp enemy.cpp myobject.cpp shuttle.cpp stage.cpp super.cpp
INC = -I./
  
OBJS = $(SRCS:.cpp=.o)  
  
$(TARGET):$(OBJS)
	$(CC) $(CFLAGS_MAKE) $(INC) -o $@ $^

%.o:%.cpp
	$(CC) $(CFLAGS_COMPLIE) $(INC) -o $@ -c $<  


clean:
	rm -rf *.o main

run:
	./main
```

打开终端，进入源代码所在目录，使用`make`命令即可编译。

运行输出的`main`可执行程序即可。

### 模块
#### 类
1. Stage       - 舞台类。
2. Background  - 背景图像和音乐
3. Bomb        - 炸弹
4. BonusLife   - 奖品类
5. Enemy       - 普通敌机
6. MyObject    - 所有实体的基类。包含必要的属性和方法
7. Shuttle     - 飞机类
8. Super       - 超级敌机类。

#### 部分源代码
```
// stage.cpp
// Draw objects on window for every frame

void Stage::drawProperties(){
	// Draw background
    m_window->draw(*m_bg);
    // Draw hero
    m_window->draw(*hero);
    // Draw score text
    m_window->draw(score);
    // Draw and move enemy shuttles
    for(std::vector<Enemy>::iterator i = m_enemies.begin(); i != m_enemies.end();){
        if(m_enemies.size() == 0){
            break;
        }
        if((*i).getLifeState()){
            (*i).animate();
            m_window->draw(*i);
            i++;
        } else {
            if((!(*i).isExplosion())){
               // After level 7, every missed enemy costs 10 points
               points -= 10 * level;
            }
            // If out of window then die
            if((*i).isOutOfWindow()){
                mutex.lock();
                i = m_enemies.erase(i);
                m_enemies.swap(m_enemies);
                mutex.unlock();
                continue;
            }
            // If a enemy is hit play explosion animation then die.
            if(((*i).isExplosion()) && !(*i).playExplodeAnimate()){
                // IMPORTANT: Method erase() returns the next iterator
                // To pass the next iterator to var i will prevent from operating wild pointer.
                mutex.lock();
                i = m_enemies.erase(i);
                m_enemies.swap(m_enemies);
                mutex.unlock();
            } else {
                m_window->draw(*i);
                i++;
            }
        }
    }
    // Draw and move bombs
    for(std::vector<Bomb>::iterator i = m_bombs.begin(); i != m_bombs.end();){
        if(m_bombs.size() == 0){
            break;
        }
        if((*i).getLifeState()){
            (*i).reloadTexture();
            (*i).shoot();
            m_window->draw(*i);
            i++;
        } else {
            mutex.lock();
            i = m_bombs.erase(i);
            m_bombs.swap(m_bombs);
            mutex.unlock();
        }
    }

    for(std::vector<Bomb>::iterator i = m_bombs_e.begin(); i != m_bombs_e.end();){
        if(m_bombs_e.size() == 0){
            break;
        }
        if((*i).getLifeState()){
            (*i).reloadTexture();
            (*i).shoot();
            m_window->draw(*i);
            i++;
        } else {
            mutex.lock();
            i = m_bombs_e.erase(i);
            m_bombs_e.swap(m_bombs_e);
            mutex.unlock();
        }
    }

    // Draw life-point bonus
    for(std::vector<BonusLife>::iterator i = m_bonus_life.begin(); i != m_bonus_life.end();){
        if(m_bonus_life.size() == 0){
            break;
        }
        if((*i).getLifeState()){
            (*i).animate();
            m_window->draw(*i);
            i++;
        } else {
            mutex.lock();
            i = m_bonus_life.erase(i);
            m_bonus_life.swap(m_bonus_life);
            mutex.unlock();
        }
    }

    // Draw super shuttles
    for(std::vector<Super>::iterator i = m_super.begin(); i != m_super.end();){
        if(m_super.size() == 0){
            break;
        }
        if((*i).getLifeState()){
            (*i).animate();
            m_window->draw(*i);
            i++;
        } else {
            mutex.lock();
            i = m_super.erase(i);
            if((*i).isExplosion()){
                points += 250;
            }
            m_super.swap(m_super);
            mutex.unlock();
        }
    }
}
```

完整源代码在本github仓库中。

#### 类之间的关系（UML图）
![UML](https://github.com/excelle08/CPP__Fighter/blob/master/fighter_uml.png?raw=true)

## 测试·程序性能
### 运行截图

![Screenshot]()

### 性能
游戏稳定的运行在60fps左右，没有明显的卡顿

输出的可执行文件main的大小有129K， 加上资源文件大约2.2M。

源代码总共有1287行。

## Comments

It's fun to play~

## 总结

1. 面向对象的程序设计
2. SFML图形库的使用
3. 处理溢出问题
4. 多线程
5. 如何写makefile