"""
Simple Python program intended to help in printing lecture slides correctly.
@author Michelle Lin
"""

class doubleSide:

    def __init__(self, pages, slidesPerPage=6):
        """Initializes print range to entire document length."""
        self.pages = range(1, pages + 1)
        self.slidesPerPage = slidesPerPage
        self.numPages = len(self.pages);

    def remove(self, pageNum):
        """Removes PAGENUM from the print range."""
        assert type(pageNum) is int, "Please enter an integer page number" % pageNum
        assert pageNum in self.pages, "Page %d doesn't exist in document" % pageNum
        self.pages.remove(pageNum)

    def generateRange(self):
        """Generates slide ranges per page, as dictated by SLIDESPERPAGE."""
        chunks = []
        for i in self.pages:
            if (i - 1) % self.slidesPerPage == 0:
                if (i + 3) > self.numPages:
                    chunks.append(str(i) + "-" + str(self.numPages))
                else:
                    chunks.append(str(i) + "-" + str(i + self.slidesPerPage - 1))
        return chunks

    def getSides(self):
        """Splits printing into odd- and even-numbered pages for double-siding."""
        odd, even = [], []
        chunks = self.generateRange()
        for index, range in enumerate(chunks):
            if index % 2 == 0:
                odd.append(chunks[index])
            else:
                even.append(chunks[index])
        print("Odd: " + ", ".join(odd))
        print("Even: " + ", ".join(even))

    def queryRemoval(self):
        remove = input("Enter page numbers to remove from printing, or '.' if done: ")
        if (remove == '.'):
            return False
        else:
            self.remove(int(remove))
            return queryRemoval()

# ===== #
# Input #
# ===== #
pages = input("Enter total number of pages in document: ")
x = doubleSide(int(pages))
x.queryRemoval()
x.getSides()
