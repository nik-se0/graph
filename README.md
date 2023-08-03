# Maximum-k-truss
Finding the maximum k-truss in an undirected unweighted graph
__Введение__
Графы распространены повсеместно. Любой набор взаимодействующих объектов может быть представлен в виде графа, где объекты являются вершинами, а взаимодействия – ребрами. Такое представление данных в виде графа используется во многих прикладных областях, например: биологические и транспортные системы, графы социальных сетей и многие др. Масштаб данных, используемых в графовой аналитике, растет беспрецедентными темпами, более чем когда-либо экспертам из разных предметных областей требуются эффективные и параллельные алгоритмы. Разработке таких реализаций для высокопроизводительных систем уделяется большое внимание в научном и техническом сообществе. Учитываются особенности обработки больших объемов таких данных: ограниченный параллелизм задач из-за работы с памятью, низкая арифметическая интенсивность, зависимость по данным между итерациями. 
Чтобы понять структуру графа, часто бывает полезно найти плотно связанные наборы вершин и ребер или подграфы в графе. Существует несколько известных задач на нахождение связанных подграфов, однако, поскольку большинство из них NP-полные, точное решение требует больших вычислительных ресурсов для графов больших порядков. 
Один из методов нахождения связанных подграфов – найти k_truss разложение графа. K-truss представляет собой иерархическую декомпозицию ребер графа и тесно связан с задачей перечисления треугольников. Такая формулировка связных подграфов полезна на практике, потому что k-truss может быть точно вычислен с использованием простых алгоритмов за полиномиальное время. В частности, k-truss — это мощный инструмент для определения структуры сообществ в графе, который может обеспечить понимание во время анализа графов. Способность эффективно вычислять декомпозицию k_truss имеет важное значение, поскольку на практике графы становятся все более большими и разреженным. 
Целью работы является программная реализация и экспериментальное исследование последовательных алгоритмов Х. Кабир и К. Маддури для вычисления разложения k_truss графа. 
