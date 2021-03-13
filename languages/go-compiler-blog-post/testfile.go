package main

type testInterface interface {
	doSomething()
}

type testStruct struct {
	variable int // used to instantiate struct
}

 func (t *testStruct) doSomething() {
	print("doing something in here!")
 }

 func main() {
 	t := &testStruct{}
 	i := testInterface(t)
	print(i)
 }
