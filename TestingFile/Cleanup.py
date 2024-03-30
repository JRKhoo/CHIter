import os

class Cleanup:    
    # initialize the class with the path to start looking for directories
    def __init__(self, path=None, target_dir_list=None, iteration=None):
        
        # define where to start looking for directories
        if isinstance(path, type(None)):
            # default to the root directory if no directory provided
            self.path = "/"
        else:
            self.path = path
            
        # define where to look for directories
        if isinstance(target_dir_list, type(None)):
            self.target_dir_list = []
        else:
            self.target_dir_list = target_dir_list
        
        # define how many times to iterate
        if isinstance(target_dir_list, type(None)):
            self.iteration = 1
        else:
            self.iteration = iteration
        
        # get own absolute path
        self.own_path = os.path.realpath(__file__)
     
    # list all directories in the given path   
    def list_directories(self,path):
        self.target_dir_list.append(path)
        files_in_current_directory = os.listdir(path)
        
        # iterate over all files in the current directory
        for file in files_in_current_directory:
            # avoid hidden files/directories (start with dot (.))
            if not file.startswith('.'):
                # get the full path
                absolute_path = os.path.join(path, file)
                print(absolute_path)

                # check if the file is a directory
                if os.path.isdir(absolute_path):
                    self.list_directories(absolute_path)
                else:
                    pass
            
    # delete target file in directories
    def delete_existing_files(self, fileName):
        for directory in self.target_dir_list:
            file_list_in_dir = os.listdir(directory)
            for file in file_list_in_dir:
                abs_path = os.path.join(directory, file)
                if file == fileName and directory != self.path:
                    os.remove(abs_path)
                
    # start the worm actions        
    def start_cleanup(self):
        self.list_directories(self.path)
        fileName = input("Enter the file name to delete: ")
        self.delete_existing_files(fileName=fileName)
        
# driver code
if __name__=="__main__":
    current_directory = os.path.abspath("")
    worm = Cleanup(path=current_directory)
    worm.start_cleanup()