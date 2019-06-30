#version 330 core 

in vec3 FragPos;  //输入
in vec3 Normal;   //法向量
in vec2 TexCoord;  //uv 坐标

struct Material
{
vec3 ambient;        //vec3纯色     sampler2D 贴图色
sampler2D diffuse;
sampler2D specuar;
float shininess;
};
   
struct LightPoint      // 定义 类型!!!!!
{
float constant; 
float linear;   
float quadratic;
};

struct LightSpot
{
 // float cosPhy;
  float cosPhyInner;  
 float cosPhyOutter ; 
};

uniform LightSpot lightS; 
uniform LightPoint lightP;    //定义变量！！！
uniform vec3 lightDirUniform;   //灯光向量
uniform Material material;  //把对象传进来！！！！！！！！！！11111     //已经把实例化对象数据拷进来了所以material.diffuse用结构体索引（变量名)名
uniform vec3 ambientColor;     //环境颜色
uniform vec3 objColor;         //物体的颜色
uniform vec3 lightPos;         
uniform vec3 lightColor;
uniform vec3 CammeraPos;   //接进来用  视点（摄像机点）

 out vec4 FragColor;  
void main() 
{    
 
  float dist=length(lightPos-FragPos);
  float attenuation= 1.0f/(lightP.constant +lightP.linear*dist+ lightP.quadratic*(dist*dist));  //点光源的衰减值
 
 vec3 lightDir=normalize(lightPos-FragPos);    //lightDir方向向量
   vec3 reflectVec=reflect(-lightDir,Normal); 
   vec3 cammeraVec=normalize(CammeraPos-FragPos);  
  
  //specular 
   float specularAmount=pow(max(dot(reflectVec,cammeraVec),0),32);   //pow次方数 衰减度 
   vec3 specular =texture(material.specuar,TexCoord).rgb*specularAmount*lightColor;                 //反应夹角的值乘意光照来反映镜面反射分量
     //diffuse	
   vec3 diffuse=texture(material.diffuse,TexCoord).rgb*max(dot(lightDir,Normal),0)*lightColor;   //根据UV坐标去图片上取对应的图片颜色
	
   vec3 ambient=texture(material.diffuse,TexCoord).rgb*ambientColor;  

   float cosTheta = dot(normalize(FragPos-lightPos),  -1 * lightDirUniform);    
  
  float spotRatio;
 if(cosTheta>lightS.cosPhyInner)
 {//inside
   spotRatio=1.0f;
 }
 else if(cosTheta>lightS.cosPhyOutter)
 {//middle
    spotRatio=1.0f-(cosTheta-lightS.cosPhyInner)/(lightS.cosPhyOutter-lightS.cosPhyInner);
 }
 else{//outsider
 spotRatio=0;
 }
  FragColor=vec4(  (ambient+ (diffuse+specular)*spotRatio)*objColor ,1.0);


 //  if(cosTheta > lightS.cosPhy)          //??????????????????????????????????????????????????????????????
//   {
//   //inside
//   FragColor=vec4(  (ambient+ (diffuse+specular))*objColor ,1.0);   //各分量相加  *attenuation //为什么不算上衰减值56行有红线加上或又时有有时没有        
//
//   }
//   else  //outside
//   {
//    FragColor=vec4( ambient *objColor ,1.0);   //各分量相加	
//
//   }
//

 } 