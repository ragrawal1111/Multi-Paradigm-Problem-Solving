"""
Assignment 7: Multi-Paradigm Problem Solving
Python Implementation - Object-Oriented Approach

Calculates mean, median, and mode of a list of integers.
Uses a StatisticsCalculator class with encapsulated methods.
"""


class StatisticsCalculator:
    """Encapsulates statistical calculations for a list of integers."""

    def __init__(self, data: list[int]):
        """Initialize with a list of integers.

        Args:
            data: A list of integers to compute statistics on.
        """
        if not data:
            raise ValueError("Data list must not be empty.")
        self._data = list(data)  # Store a copy to preserve immutability
        self._sorted_data = sorted(self._data)

    @property
    def data(self) -> list[int]:
        """Return the original data."""
        return list(self._data)

    @property
    def sorted_data(self) -> list[int]:
        """Return the sorted data."""
        return list(self._sorted_data)

    def calculate_mean(self) -> float:
        """Calculate and return the mean (average) of the data."""
        return sum(self._data) / len(self._data)

    def calculate_median(self) -> float:
        """Calculate and return the median of the data."""
        n = len(self._sorted_data)
        mid = n // 2
        if n % 2 == 1:
            return float(self._sorted_data[mid])
        else:
            return (self._sorted_data[mid - 1] + self._sorted_data[mid]) / 2.0

    def calculate_mode(self) -> tuple[list[int], int]:
        """Calculate and return the mode(s) and their frequency.

        Returns:
            A tuple of (list of mode values, frequency count).
        """
        # Build frequency dictionary
        frequency: dict[int, int] = {}
        for value in self._data:
            frequency[value] = frequency.get(value, 0) + 1

        # Find maximum frequency
        max_freq = max(frequency.values())

        # Collect all values with the maximum frequency
        modes = sorted([key for key, count in frequency.items() if count == max_freq])

        return modes, max_freq

    def display_results(self) -> None:
        """Display all computed statistics."""
        print(f"Input data: {self._data}")
        print(f"Number of elements: {len(self._data)}\n")
        print(f"Sorted data: {self._sorted_data}\n")

        mean = self.calculate_mean()
        median = self.calculate_median()
        modes, freq = self.calculate_mode()

        print("--- Results ---")
        print(f"Mean:   {mean:.2f}")
        print(f"Median: {median:.2f}")

        if freq == 1:
            print("Mode:   No mode (all values appear once)")
        else:
            print(f"Mode:   {modes} (each appears {freq} times)")


def main():
    """Main function demonstrating the StatisticsCalculator class."""
    # First dataset
    data1 = [4, 7, 2, 9, 1, 5, 7, 3, 7, 2, 8, 6, 5, 3, 7]
    print("=== Statistics Calculator (Python - Object-Oriented) ===\n")
    calc1 = StatisticsCalculator(data1)
    calc1.display_results()

    print("\n========================================\n")

    # Second dataset with multiple modes
    data2 = [10, 20, 20, 30, 30, 40, 50]
    print("=== Statistics Calculator (Python - Object-Oriented) ===\n")
    calc2 = StatisticsCalculator(data2)
    calc2.display_results()


if __name__ == "__main__":
    main()
