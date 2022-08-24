# Solved:
# (M) My Calendar I
# https://leetcode.com/problems/my-calendar-i/

class MyCalendar:

    def __init__(self):
        self.booking = []

    def _searchInBookings(self, start: int) -> int:
        l: int = 0
        r: int = len(self.booking) - 1

        while l <= r:
            m = (l + r) >> 1
            x = self.booking[m][0]
            if x == start:
                return m
            if start < x:
                r = m - 1
            else:
                l = m + 1
        return l

    def book(self, start: int, end: int) -> bool:
        if self.booking:
            # If the new booking ends before first booking
            if end <= self.booking[0][0]:
                self.booking.insert(0, (start, end))
                return True
            # If the new booking starts after the last booking ends
            if start >= self.booking[-1][1]:
                self.booking.append((start, end))
                return True
            # Searching for the booking that starts just before new booking start
            idx = self._searchInBookings(start)
            # If the new booking completely puts between two consecutive bookings
            if 0 < idx < len(self.booking) and start >= self.booking[idx - 1][1] and end <= self.booking[idx][0]:
                self.booking.insert(idx, (start, end))
                return True

            return False
        else:
            self.booking.append((start, end))
            return True


x = MyCalendar()

print(x.booking)

lst = [[20,29],[13,22],[44,50],[1,7],[2,10],[14,20],[19,25],[36,42],[45,50],[47,50],[39,45],[44,50],[16,25],[45,50],
       [45,50],[12,20],[21,29],[11,20],[12,17],[34,40],[10,18],[38,44],[23,32],[38,44],[15,20],[27,33],[34,42],[44,50],
       [35,40],[24,31]]

for b in lst:
    print(b, x.book(b[0], b[1]))

print(x.booking)
