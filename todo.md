# ProLex Analytics

### [./test/test.cpp[14:14]](./test/test.cpp#L14)
valid path has been passed, possible change?
```cpp
this->basePath=_baseDirectory;
```
### [./test/test.cpp[33:36]](./test/test.cpp#L33-L36)
Sample
```cpp
std::smatchsm;
vector<string>files;
for(autofile:fs::recursive_directory_iterator(this->basePath))
```
### [./test/test.cpp[45:48]](./test/test.cpp#L45-L48)
[TODO] Use printff();
```cpp
printf("Filefound[%s]\n",file.path().c_str());
}
}
```
### [./test/test.cpp[65:67]](./test/test.cpp#L65-L67)
Need to reflect the MINE type back to the header generator
```cpp
this->fVector.push_back(file.path());
printf("Filefound[%s]\n",file.path().c_str());
```
