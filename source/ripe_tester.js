function runTest(attack) {
    if(attack == "all") {
        console.log("Attack 1: Stack overflow & strcpy function")
        try {
            callMain(["stackoverflow", "strcpy"])
        } catch (e) {
            console.log("Stack overflow attack failed!")
        }
        console.log("Attack 2: Stack overflow & strncpy function")
        try {
            callMain(["stackoverflow", "strncpy"])
        } catch (e) {
            console.log("Stack overflow attack failed!")
        }
        console.log("Attack 3: Stack overflow & memcpy function")
        try {
            callMain(["stackoverflow", "memcpy"])
        } catch (e) {
            console.log("Stack overflow attack failed!")
        }
    
        console.log("Attack 4: Indirect call redirection & strcpy function")
        try {
            callMain(["indirectcall", "strcpy"])
        } catch (e) {
            console.log("Indirect call redirection failed!")
        }
        console.log("Attack 5: Indirect call redirection & strncpy function")
        try {
            callMain(["indirectcall", "strncpy"])
        } catch (e) {
            console.log("Indirect call redirection failed!")
        }
        console.log("Attack 6: Indirect call redirection & memcpy function")
        try {
            callMain(["indirectcall", "memcpy"])
        } catch (e) {
            console.log("Indirect call redirection failed!")
        }
    
        console.log("Attack 7: Rodata constant overwrite & strcpy function")
        try {
            callMain(["rodataoverwrite", "strcpy"])
        } catch (e) {
            console.log("Rodata constant overwrite failed!")
        }
        console.log("Attack 8: Rodata constant overwrite & strncpy function")
        try {
            callMain(["rodataoverwrite", "strncpy"])
        } catch (e) {
            console.log("Rodata constant overwrite failed!")
        }
        console.log("Attack 9: Rodata constant overwrite & memcpy function")
        try {
            callMain(["rodataoverwrite", "memcpy"])
        } catch (e) {
            console.log("Rodata constant overwrite failed!")
        }
    }

    else if(attack == "stackoverflow") {
        console.log("Attack 1: Stack overflow & strcpy function")
        try {
            callMain(["stackoverflow", "strcpy"])
        } catch (e) {
            console.log("Stack overflow attack failed!")
        }
        console.log("Attack 2: Stack overflow & strncpy function")
        try {
            callMain(["stackoverflow", "strncpy"])
        } catch (e) {
            console.log("Stack overflow attack failed!")
        }
        console.log("Attack 3: Stack overflow & memcpy function")
        try {
            callMain(["stackoverflow", "memcpy"])
        } catch (e) {
            console.log("Stack overflow attack failed!")
        }
    }

    else if(attack == "indirectcall") {
        console.log("Attack 1: Indirect call redirection & strcpy function")
        try {
            callMain(["indirectcall", "strcpy"])
        } catch (e) {
            console.log("Indirect call redirection failed!")
        }
        console.log("Attack 2: Indirect call redirection & strncpy function")
        try {
            callMain(["indirectcall", "strncpy"])
        } catch (e) {
            console.log("Indirect call redirection failed!")
        }
        console.log("Attack 3: Indirect call redirection & memcpy function")
        try {
            callMain(["indirectcall", "memcpy"])
        } catch (e) {
            console.log("Indirect call redirection failed!")
        }
    }

    else if(attack == "rodataoverwrite") {
        console.log("Attack 1: Rodata constant overwrite & strcpy function")
        try {
            callMain(["rodataoverwrite", "strcpy"])
        } catch (e) {
            console.log("Rodata constant overwrite failed!")
        }
        console.log("Attack 2: Rodata constant overwrite & strncpy function")
        try {
            callMain(["rodataoverwrite", "strncpy"])
        } catch (e) {
            console.log("Rodata constant overwrite failed!")
        }
        console.log("Attack 3: Rodata constant overwrite & memcpy function")
        try {
            callMain(["rodataoverwrite", "memcpy"])
        } catch (e) {
            console.log("Rodata constant overwrite failed!")
        }
    }

    else {
        console.log("Please enter the type of attack [\"all\", \"stackoverflow\", \"indirectcall\", \"rodataoverwrite\"]")
    }
}