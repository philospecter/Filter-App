PIXELFORGE — C++/CLI Windows Forms GUI for the 18 image operations

الملفات:
- Main.cpp: نقطة تشغيل واجهة Windows Forms.
- MyForm.h: تصميم الواجهة وربط الأزرار.
- Filters.h / Filters.cpp: عمليات معالجة الصور الـ18 بكود C++ عادي.

مهم قبل التشغيل:
1) افتح مشروع Windows Forms C++/CLI الذي عندك في Visual Studio.
2) انسخ الملفات الأربعة إلى مجلد المشروع بجانب ملف Image_Class.h.
3) أضف Main.cpp وFilters.cpp إلى المشروع من Project > Add > Existing Item.
4) استبدل محتوى MyForm.h بالملف المرفق، أو أضفه إذا كان مشروعًا جديدًا.
5) تأكد أن Image_Class.h موجود بجانب Filters.cpp وMyForm.h. لا تنسخ ملفًا مختلفًا أو نسخة قديمة من الكلاس.
6) من Project Properties > General تأكد أن Common Language Runtime Support مضبوط على /clr.
7) اجعل Main.cpp هو نقطة الدخول الوحيدة. لو عندك ملف تشغيل آخر فيه main، لا تترك الاثنين معًا.
8) Build ثم Run.

طريقة الاستخدام:
- Load image لتحميل الصورة.
- اكتب رقم العملية من 1 إلى 18 في خانة FILTER NUMBER.
- Apply operation لتطبيقها. بعض العمليات ستطلب أرقامًا إضافية أو صورة ثانية.
- Save result لحفظ الناتج.

الأرقام:
1 Grayscale | 2 Black & White | 3 Invert | 4 Frame | 5 Flip | 6 Rotate
7 Darken/Lighten | 8 Resize | 9 Merge | 10 Edge Detection | 11 Crop | 12 Blur
13 Improve Sunlight | 14 Old TV | 15 Purple | 16 Infrared | 17 Skew | 18 Oil Painting

ملاحظات:
- الواجهة مبنية بـ C++/CLI Windows Forms، ومعالجة الصور في Filters.cpp بلغة C++ عادية، وليست C#.
- يعتمد المشروع على نسخة Image_Class.h التي تستخدم Image(filename)، وgetPixel(x,y,channel)، وsetPixel(x,y,channel,value)، وsaveImage(filename).
- تم اختبار سلامة إنشاء الملفات فقط في هذه البيئة؛ لا يمكن تأكيد البناء النهائي دون ملف Image_Class.h ومشروع Visual Studio الأصلي. إذا ظهر خطأ build، ابعت نص الخطأ كاملًا.
