
"""
Gilad Meir - 313416562
"""

import csv,os,json
class DataSummary:
    
    def __init__(self,datafile=" ",metafile=" "):
        print(datafile,metafile)
        if not datafile or not metafile:
            raise ValueError("Datafile or metafile does not exist")
        f=open(datafile)
        self.data=json.load(f)
        for val in self.data.values():
                self.list_of_jsons=(val)
        f=open(metafile)
        reader=csv.reader(f)
        self.entities=next(reader)
        
        
        #    DELETE (KEY,VAL) THAT'S NOT EXIST IN CSV FILE    #
        
        for item in self.list_of_jsons:
            for key in item:
                for ent in self.entities:
                    flag=1
                    if(key==ent):
                        flag=0
                        break
                if (flag):
                    del item[key]

        for item in self.list_of_jsons:
            for ent in self.entities:
                for key in item:
                    flag=1
                    if(key==ent):
                        break
                    else:
                        item[ent]=None
                
            
                
                
    def __getitem__(self,index):
        """
        *** getitem method override ***

        Parameters
        ----------
        index : int
            get item by index from the original json file

        Returns
        -------
        dictionary of the i'th record

        """
        if index in range(len(self.list_of_jsons)):
            return(self.list_of_jsons[index])
                
        
        
        
        # **************** PRIVATE METHODS **************** #
        
            

        
        
        
        
        
    def gilad(self):


        # PRINT JSON RECORDS WITH INDEXES FROM 0 #
        
        for i in range(len(self.list_of_jsons)):
            print(i,'.',self.list_of_jsons[i],'\n')  
        

                
                    
        
        
        
DS = DataSummary(datafile="happiness.json",metafile="happiness_meta.csv")
DS.gilad()
        
        