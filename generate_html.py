
html = r"""
<!DOCTYPE html>
<html lang="en">
<head>
    <meta name="google-site-verification" content="4DlfvgCFfSNN_VpDVQx-isnRSV1AK2o6XVFFNf9Tuo8" />
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Embedded C Preparation</title>
    <style>
        body {
            font-family: sans-serif;
            display: flex;
            margin: 0;
        }

        nav {
            width: 250px;
            background-color: #f0f0f0;
            padding: 20px;
            border-right: 1px solid #ccc;
        }

        nav ul {
            list-style: none;
            padding: 0;
        }

        nav li a {
            display: block;
            padding: 10px;
            text-decoration: none;
            color: #333;
            cursor: pointer;
        }

        nav li a:hover {
            background-color: #ddd;
        }

        main {
            flex: 1;
            padding: 20px;
        }

        section {
            display: none; /* Initially hide all sections */
            margin-bottom: 20px;
        }

        h2 {
            margin-top: 0;
        }

        .section-content {
            display: none; /* Initially hide all section content */
        }

        #home {
            display: block; /* Show home by default */
        }
    </style>
</head>
<body>

    <nav>
        <h2>Table of Contents</h2>
        <ul>
            <li><a data-target="home">Home</a></li>
            <li><a data-target="section1">Numbers</a></li>
            <li><a data-target="section2">Arrays</a></li>
            <li><a data-target="section3">Strings</a></li>
            <li><a data-target="section4">Pointers</a></li>
            <li><a data-target="section5">Structures</a></li>
            <li><a data-target="section6">Linked Lists</a></li>
        </ul>
    </nav>

    <main>
        <section id="home">
            <h2>Home</h2>
            <p>Welcome to the home page! This is the default content.</p>
        </section>

        <section id="section1">
            <h2>Numbers</h2>
            <div class="section-content">
                <h3>Q1. WAP to print fibonacci series</h3>
                <p>C questions on Numbers.</p>
                <h3>Q2. WAP to swap two numbers</h3>
                <p>C questions on Numbers.</p>
                <h3>Q3. WAP to compute the sign of an integer</h3>
                <p>C questions on Numbers.</p>
                <h3>Q4. WAP to convert integer to binary</h3>
                <p>C questions on Numbers.</p>
                <h3>Q5. WAP to convert binary to integer</h3>
                <p>C questions on Numbers.</p>
                <h3>Q6. WAP to find if a number is power of 2</h3>
                <p>C questions on Numbers.</p>
                <h3>Q7. WAP to find if a number is power of 4</h3>
                <p>C questions on Numbers.</p>
                <h3>Q8. WAP to find if a number is power of 8</h3>
                <p>C questions on Numbers.</p>
                <h3>Q9. WAP to round a number to next poewer of 2</h3>
                <p>C questions on Numbers.</p>
                <h3>Q10. WAP to check endianness of a system</h3>
                <p>C questions on Numbers.</p>
                <h3>Q11. WAP to change endianness of a system</h3>
                <p>C questions on Numbers.</p>
                <h3>Q12. WAP to find absolute value of a number</h3>
                <p>C questions on Numbers.</p>
                <h3>Q13. WAP to rotate bits of a number</h3>
                <p>C questions on Numbers.</p>
                <h3>Q14. WAP to reverse bits of a number</h3>
                <p>C questions on Numbers.</p>
                <h3>Q15. WAP to swap even and odd bits of a number</h3>
                <p>C questions on Numbers.</p>
                <h3>Q16. WAP to count number of bit flips needed to convert number A to number B</h3>
                <p>C questions on Numbers.</p>
                <h3>Q17. WAP to find parity of a number</h3>
                <p>C questions on Numbers.</p>
            </div>
        </section>

        <section id="section2">
            <h2>Arrays</h2>
            <div class="section-content">
                <h3>Q1. WAP to sort an array</h3>
                <p>C questions on Numbers.</p>
                <h3>Q2. WAP to sort an array with 0, 1 and 2</h3>
                <p>C questions on Numbers.</p>
                <h3>Q3. WAP to cyclically rotate an array by one</h3>
                <p>C questions on Numbers.</p>

            </div>
        </section>

        <section id="section3">
            <h2>Strings</h2>
            <div class="section-content">
                <p>C questions on Strings.</p>
            </div>
        </section>

        <section id="section4">
            <h2>Pointers</h2>
            <div class="section-content">
                <p>C questions on Pointers.</p>
            </div>
        </section>

        <section id="section5">
            <h2>Structures</h2>
            <div class="section-content">
                <p>C questions on Structures.</p>
            </div>
        </section>

        <section id="section6">
            <h2>Linked Lists</h2>
            <div class="section-content">
                <p>C questions on Linked Lists.</p>
            </div>
        </section>

    </main>

    <script>
        const navLinks = document.querySelectorAll('nav a');
        const sections = document.querySelectorAll('section');

        navLinks.forEach(link => {
            link.addEventListener('click', (event) => {
                event.preventDefault();

                const targetId = event.target.dataset.target;

                sections.forEach(section => {
                    if (section.id === targetId) {
                        section.style.display = 'block'; // Show the clicked section
                        const content = section.querySelector('.section-content');
                        if (content) {
                            content.style.display = content.style.display === 'block' ? 'none' : 'block'; // Toggle content
                        }
                    } else {
                        section.style.display = 'none'; // Hide other sections
                        const content = section.querySelector('.section-content');
                        if (content) {
                            content.style.display = 'none'; // Hide content of other sections
                        }
                    }
                });
            });
        });


    </script>

</body>
</html>
"""

# print (html)

toc = {"Numbers"} # {"Numbers", "Arrays", "Strings", "Pointers", "Structures", "Linked_Lists", "Embedded"}

from os import walk
import os
import glob

mypath = os.path.dirname(os.path.abspath(__file__))

f = []
# for (dirpath, dirnames, filenames) in walk(mypath):
#     f.extend(filenames)
#     break

filename = ""
brief = ""

f = glob.glob(mypath + "/*/*.c")

for heading in toc:
    for file in f:
        if heading.lower() in file:
            print(heading, ": ", file)
            fr = open(file, 'r')
            lines = fr.readlines()
            for line in lines:
                if "@file" in line:
                    filename = line.split("@file ")[1]
                if r"@brief" in line:
                    brief = line.split("@brief ")[1]
            print("Path", ": ", file)
            print("File name", ": ", filename)
            print("Brief", ": ", brief)

