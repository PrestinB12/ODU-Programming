import sys
# import numpy

def decimal_to_binary(decimal):
    binary = "0."
    while decimal > 0:
        decimal *= 2
        bit = int(decimal)
        binary += str(bit)
        decimal -= bit
        
        if len(binary) > 34:  
            break
    return binary

def main():

    args = sys.argv[1:]
    
    
    print("| Base 10 | Base 2 |")   # Prints the header/format
    print("| :-------|:-------|")
    
   # python3 convert_dec_to_bin.py 0.5 0.25 0.75

    for arg in args:    # Processes the number
        try:
           
            decimal_value = float(arg)   # Converts the number
            
            
            if 0 <= decimal_value < 1:  # Check if the num is within the range
                binary_value = decimal_to_binary(decimal_value)
                print(f"| {decimal_value} | {binary_value} |")
            else:
                print(f"| {arg} | INVALID RANGE |") # Error message
        except ValueError:
            print(f"| {arg} | INVALID INPUT |")

if __name__ == "__main__":
    main()
