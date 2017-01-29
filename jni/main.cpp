#include <jni.h>
#include <dlfcn.h>
#include <Substrate.h>
#include <string>

class BlockEntity{};
class SignBlockEntity:public BlockEntity{
public:
std::string& getMessage(int) const;
};
class BlockSource{
public:
BlockEntity* getBlockEntity(int,int,int);
int getBlockID(int,int,int);
};
class Entity{
public:
BlockSource& getRegion() const;
};
class MinecraftClient{
public:
void update();
bool isInGame();
};
class MinecraftScreenModel{
public:
MinecraftScreenModel(MinecraftClient &);
void executeCommand(const std::string&);
};
class ItemInstance;
class Item{
public:
bool useOn(ItemInstance&,Entity&, int, int, int, signed char, float, float, float);
};

MinecraftClient* model;

void (*_MinecraftClient$update)(MinecraftClient*);
void MinecraftClient$update(MinecraftClient* client){
 _MinecraftClient$update(client);
 model=client;
};
MinecraftScreenModel* temp;
bool (*_Item$useOn)(Item*,ItemInstance&,Entity&, int, int, int, signed char, float, float, float);
bool Item$useOn(Item* item,ItemInstance& inst,Entity& ent, int x, int y, int z, signed char side, float xx, float yy, float zz){
 SignBlockEntity* sign=(SignBlockEntity*)ent.getRegion().getBlockEntity(x,y,z);
 if(model!=nullptr){
  if(temp==nullptr)
   temp=new MinecraftScreenModel(*model);
 }
 if(sign!=nullptr){
  for(int i=0;i<4;i++){
   std::string str=sign->getMessage(i);
    if(str.find("/")!=std::string::npos){
     temp->executeCommand(str);
    }
   }
  }
 return _Item$useOn(item,inst,ent,x,y,z,side,xx,yy,zz);
};

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved){
 MSHookFunction((void*)&MinecraftClient::update,(void*)&MinecraftClient$update,(void**)&_MinecraftClient$update);
 MSHookFunction((void*)&Item::useOn,(void*)&Item$useOn,(void**)&_Item$useOn);
	return JNI_VERSION_1_2;
}
