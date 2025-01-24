# Kendall's Tau Rank Correlation and Movie Rankings

This project implements a program to calculate Kendall's Tau Rank Correlation Coefficient, a measure of similarity between two rankings, using a movie-ranking scenario. The program compares rankings provided by two individuals, computes similarity and dissimilarity percentages, and provides a detailed analysis of concordant and discordant pairs.

## Features
- **Kendall's Tau Calculation**: Computes the correlation coefficient to evaluate the similarity between two ranking lists.
- **Concordant and Discordant Pairs**: Identifies and displays pairs of rankings that are similar (concordant) or dissimilar (discordant).
- **Similarity and Dissimilarity Analysis**:
  - Outputs the percentage of similarity and dissimilarity between two rankings.
  - Concludes whether the rankings are similar or not based on the analysis.
- **Detailed Movie Rankings**:
  - Displays ranked lists for both individuals.
  - Provides pairwise comparisons of movies based on rankings.

Users are prompted to enter their rankings for the movies. The program then:
1. Compares the two sets of rankings.
2. Calculates and outputs the Kendall's Tau Rank Correlation Coefficient.
3. Provides insights on the similarity or dissimilarity of preferences.

## How It Works
1. **Input**: Users provide their rankings for a list of movies.
2. **Processing**:
   - Computes concordant and discordant pairs using an efficient merge-sort-based approach.
   - Calculates the Kendall's Tau coefficient.
3. **Output**:
   - Displays ranked lists.
   - Lists concordant and discordant pairs.
   - Outputs similarity and dissimilarity percentages.
   - Concludes whether the rankings are similar.
