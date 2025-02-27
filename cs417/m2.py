import sys
# import numpy


MAX_DIGITS = 8  # Limit the number of digits after conversion


def decimal_to_base(decimal, base): # This converts a decimal to any base
    result = ""
    while decimal > 0 and len(result) < MAX_DIGITS:
        decimal *= base
        digit = int(decimal)

        # Append the appropriate digit to the result

        if digit < 10:
            result += str(digit)
        else:
            result += chr(digit - 10 + ord('A'))  # For bases greater than 10
        decimal -= digit

    return result

def main():
    
    args = sys.argv[1:] 
    
    if len(args) < 2:
        print("Usage: python3 convert_dec_to_any.py <base> <decimal1> <decimal2> ...")
        return

    # Parses the base
    try:
        base = int(args[0])
        if base < 2 or base > 60:
            print("Base should be between 2 and 60.")
            return
    except ValueError:
        print("Invalid base input.")
        return

     
    print(f"| Base 10 | Base {base} |") # Prints the table
    print(f"| :-------|:--------|")
    
    
    for arg in args[1:]:    # Process each decimal number
        try:
            decimal_value = float(arg)
            
            if 0 <= decimal_value < 1:  # Checks if the decimal is allowed
                base_value = decimal_to_base(decimal_value, base)
                # Formats the base (semicolon represents a new digit)
                formatted_base_value = ";".join(base_value)
                print(f"| {decimal_value} | {formatted_base_value} |")
            else:
                print(f"| {arg} | INVALID RANGE |")  # If the number is out of range
        except ValueError:
            print(f"| {arg} | INVALID INPUT |")  # If the number is not a valid number

if __name__ == "__main__":
    main()
