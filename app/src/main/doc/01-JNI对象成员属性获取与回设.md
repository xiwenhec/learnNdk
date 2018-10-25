## 成员属性的获取与回设

当我们在`java`层声明了一个`native`函数,在`JNI`层需要按着一定的格式定义一个与之关联
的函数.
例如:
```java
     //java层的函数
     public native void accessField();
```

```c
    //JNI层与java层关联的函数
    JNIEXPORT void JNICALL
    Java_com_sivin_learnndk_lesson01_NativeApi_accessField(JNIEnv *env, jobject instance)
```

其中env是我们调用`JNI`层函数的句柄指针,而instance是一个对象,这个对象对应着`java`层这个类的一个实例.

我们知道,我们在java层可以很容易的获取到某个类对象的成员属性,前提是我们必须获取到一个对象实例.

同样道理,如果我们想在`C/C++`里用到java层的某个对象的成员属性,我们该怎么办呢?
 > * 定义一个Native函数,然后将这个对象的成员属性值,然后通过参数传递的方式,传递到`Native`层

 这个是一种方式,但是这种方式使用场景太单一,简单的场景可以这么做,单对于工程开发,明显走不通.

 我们猜想,是不是也可以像java层那样,通过这个对象的实例获取呢?答案是肯定的.

 这里我们就介绍获取java层对象实例属性的另一种方式.

> 1. 首先我们需要知道这个对象是属于哪个类的
```
    //1.获取这个对象的jclass对象,第二个参数传递的就是目标对象
    jclass jclz = (*env)->GetObjectClass(env,instance);
```






