### Q : 2 adet taskımız olsun ve concurent bir şekilde çalıştıklarını varsayalım. Bu Taskların ikiside uartı kullanmak istediğini varsayalım. Task1 tam transmit ediceği sırada tick interrupt olusuyor ve schedular task2 yi cagiriyor. o taskta cevre birimini kullanmak isterse ne olur?
- Bunu sayma semaforlarıyla yaparız. Kaynak yönetimi kullanarak sırayla hangi taska semaforu verip uartı kullanmasına izin verebiliriz.
### Q : Queue yapısını kim yonetir. Kaydırma işlemini kim yapar ?
- Queue Management yapısı bu yönetimi sağlar. Biz sadece queue'a item ekleyip cikariyoruz. Tüm RAM yönetimini arkadaki Queue Manager halleder.

### Q: Taskları tanımlarken özellikle statik olarak belirtmemize gerek varmı ?