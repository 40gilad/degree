
"""
Gilad Meir - 313416562
"""

import csv,os,json
class DataSummary:
    
    category_type={"Country":type("a"),"Region":type("a"),"Happiness Rank":type(1),
                       "Happiness Score":type(1.2),"Standard Error":type(1.2),
                       "Economy":type(1.2),"Family":type(1.2),"Class":type("a")}
    
    def __init__(self,datafile=" ",metafile=" "):
        """
        DataSummary class constructor

        Parameters
        ----------
        datafile : <filename.json>
        metafile : <filename.csv>

        Raises
        ------
        ValueError
            All c'tor args must be deliverd

        Returns
        -------
        None.

        """
        if not datafile or not metafile:
            raise ValueError("Datafile or metafile does not exist")
        f=open(datafile)
        self.data=json.load(f)
        for val in self.data.values():
                self.list_of_jsons=(val)
        f.close()
        f=open(metafile)
        reader=csv.reader(f)
        self.entities=next(reader)
        f.close()
        
#*************** Removing items from json file without entitie in csv *********#

        
        for item in self.list_of_jsons:
            for key in item.copy():
                for ent in self.entities:
                    flag=1
                    if(key==ent):
                        flag=0
                        break
                if (flag):
                    del item[key]
                    
#*************** Adding missing entities to json file with None value *********#
        
        for item in self.list_of_jsons:
            for ent in self.entities:
                for key in item.copy():
                    flag=1
                    if(key==ent):
                        flag=0
                        break
                if(flag):
                    item[ent]=None
                    

    def is_number(self,value):
        """
        

        Parameters
        ----------
        value : TYPE

        Returns
        -------
        bool
            True if value is int or float

        """
        int_type=type(1)
        float_type=type(1.1)
        if (self.category_type[value]==int_type or self.category_type[value]==float_type):
            return True
        return False

        
        

                
    def __getitem__(self,index):
        """
        *** getitem method override ***

        Parameters
        ----------
        index (table row/column) : int/str

        Raises
        ------
        ValueError
            IndexError When index is out of
            KeyError when key not exist
            
        Returns
        -------
        int- dictionary copy of the i'th record
        str- list copy of the whole key values
        """
        is_int=isinstance(index, int)
        
        if(is_int):
            index-=0
            if(index>len(self.list_of_jsons)):
                raise IndexError("index is out of bound")
            if index in range(len(self.list_of_jsons)):
                return(self.list_of_jsons[index].copy())
        
        else:
            for ent in self.entities:
                if (index==ent):
                    vals_list=list()
                    for item in self.list_of_jsons:
                        for key in item:
                            if(index==key):
                                vals_list.append(item[key])
                    return vals_list
                else:
                    raise KeyError('Key not exist')
                

    def sum(self,feature):
        """
        

        Parameters
        ----------
        feature : str

        Raises
        ------
        TypeError
            value must be int/float

        Returns
        -------
        res : float
            return the sum of all values in the feature. 

        """
        res=0
        if(self.is_number(feature)):
            for item in self.list_of_jsons:
                if(item[feature]):
                    try:
                        res+=int(item[feature]) 
                    except:
                        res+=float(item[feature]) 
            return res
        else:
            raise TypeError
                
        
    def count(self,feature):
        """

        Parameters
        ----------
        feature : str

        Returns
        -------
        res : int/float
            return the number of non-None values in the feature. 

        """
        res=0
        for item in self.list_of_jsons:
            if(item[feature]):
                res+=1
        return res
        
        
    def mean(self,feature):
        """
        
        Parameters
        ----------
        feature : str

        Returns
        -------
        TYPE : float
            return the average over all values in the feature (None values are not  counted) 

        """
        return (self.sum(feature)/self.count(feature))
    
            
    def min(self,feature):
        """
        

        Parameters
        ----------
        feature : str

        Raises
        ------
        TypeError
            value must be int/float

        Returns
        -------
        res : int/float
            return the minimal value in the feature. 

        """
        
        res=100000000000
        if self.is_number(feature):
                for item in self.list_of_jsons:
                    if(item[feature] and float(item[feature])<float(res)):
                        res=item[feature]
                return res
        else:
            raise TypeError
            
            
            
    def max(self,feature):
        """
        

        Parameters
        ----------
        feature : str

        Raises
        ------
        TypeError
            value must be int/float

        Returns
        -------
        res : int/float
            return the maximal value in the feature. 

        """
        
        res=0
        if self.is_number(feature):
                    for item in self.list_of_jsons:
                        if(item[feature] and float(item[feature])>float(res)):
                            res=item[feature]
                    return res
        else:
                raise TypeError
        
           
    def mode(self,feature):
        """
        

        Parameters
        ----------
        feature : str

        Returns
        -------
        res : list
            return a list of the values which appear the most in the feature (None  values are not counted). 

        """
        sum_dict={}
        res=[]
        max=1
        for item in self.list_of_jsons:
            if(item[feature]):
                try:
                    sum_dict[item[feature]]+=1
                except:
                    sum_dict[item[feature]]=1
                if(sum_dict[item[feature]]==max):
                    continue
                if (sum_dict[item[feature]]>max):
                    max+=1
        for key in sum_dict:
            if sum_dict[key]==max:
                res.append(key)
        return res
    
    
                    
    def unique(self,feature):
        """
        

        Parameters
        ----------
        feature : str

        Returns
        -------
        res : list
            return a list of unique values in the feature

        """
        
        sum_dict={}
        res=[]
        for item in self.list_of_jsons:
            if(item[feature]):
                try:
                    sum_dict[item[feature]]+=1
                except:
                    sum_dict[item[feature]]=1
        for key in sum_dict:
            if sum_dict[key]==1:
                res.append(key)
        return res

        
    def empty(self,feature):
        """
        

        Parameters
        ----------
        feature : str

        Returns
        -------
        res : int
            return the number of None values in the feature.

        """
        
        res=0
        for item in self.list_of_jsons:
            if(not item[feature]):
                res+=1
        return res
    
    
    def to_csv(self,filename,delimiter=','):
        """
        

        Parameters
        ----------
        filename: str.csv
        delimiter: one of the following: ".", ":", "|", "-",";", "#", "*"
            DEFAULT DELIMITER: ","
        """
        
        delis=[".", ":", "|", "-",";", "#", "*"]
        temp={}
        mylist=[]
        if delimiter not in delis:
            delimiter=','
        f=open(filename,'w')
        writer=csv.writer(f,delimiter=delimiter)
        writer.writerow(self.entities)
        for item in self.list_of_jsons:
            mylist=item.values()
            writer.writerow(mylist)
        f.close()
        
                







        