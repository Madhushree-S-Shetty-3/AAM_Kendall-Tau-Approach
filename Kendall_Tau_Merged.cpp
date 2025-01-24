#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;

int mergeAndCount(vector<pair<int, int>>& arr, int left, int mid, int right, vector<pair<int, int>>& discordantPairs) {
	int invCount = 0;
	int n1 = mid - left + 1;
	int n2 = right - mid;

	vector<pair<int, int>> leftArr(n1), rightArr(n2);

	for (int i = 0; i < n1; i++) leftArr[i] = arr[left + i];
	for (int i = 0; i < n2; i++) rightArr[i] = arr[mid + 1 + i];

	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2) {
		if (leftArr[i].second <= rightArr[j].second) {
			arr[k++] = leftArr[i++];
		} else {
			discordantPairs.push_back({leftArr[i].second, rightArr[j].second});
			arr[k++] = rightArr[j++];
			invCount += (n1 - i);
		}
	}

	while (i < n1) arr[k++] = leftArr[i++];
	while (j < n2) arr[k++] = rightArr[j++];

	return invCount;
}

int mergeSortAndCount(vector<pair<int, int>>& arr, int left, int right, vector<pair<int, int>>& discordantPairs) {
	if (left >= right) return 0;
	int mid = left + (right - left) / 2;
	int invCount = mergeSortAndCount(arr, left, mid, discordantPairs);
	invCount += mergeSortAndCount(arr, mid + 1, right, discordantPairs);
	invCount += mergeAndCount(arr, left, mid, right, discordantPairs);
	return invCount;
}

void displayRankings(const vector<int>& rankings, const vector<string>& movies) {
	vector<pair<int, string>> sortedRankings;
	for (int i = 0; i < rankings.size(); ++i) {
		sortedRankings.push_back({rankings[i], movies[i]});
	}

	sort(sortedRankings.begin(), sortedRankings.end());

	for (int i = 0; i < sortedRankings.size(); ++i) {
		cout << "Rank " << sortedRankings[i].first << ": " << sortedRankings[i].second << endl;
	}
}

double kendallTau(const vector<int>& A, const vector<int>& B, const vector<string>& movies) {
	int n = A.size();
	vector<pair<int, int>> rankPairs(n);

	for (int i = 0; i < n; i++) {
		rankPairs[i] = {A[i], B[i]};
	}

	sort(rankPairs.begin(), rankPairs.end());

	vector<pair<int, int>> bRanks(n);
	for (int i = 0; i < n; i++) {
		bRanks[i] = {rankPairs[i].first, rankPairs[i].second};
	}

	vector<pair<int, int>> discordantPairs;
	int inversions = mergeSortAndCount(bRanks, 0, n - 1, discordantPairs);

	int totalPairs = n * (n - 1) / 2;
	int concordantPairs = totalPairs - inversions;
	double tau = double(concordantPairs - inversions) / totalPairs;

	cout << "\nRanked List of Movies for Person A:\n";
	displayRankings(A, movies);

	cout << "\nRanked List of Movies for Person B:\n";
	displayRankings(B, movies);

	cout << "\n\nConcordant Pairs (Similar):\n\n";
	int k=1;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (B[i] < B[j] && A[i] < A[j]) {
				cout <<k<< ". (" << movies[A[i] - 1] << ", " << movies[A[j] - 1] << ")\n";
				k++;
			}
		}
	}

	cout << "\n\nDiscordant Pairs (Dissimilar):\n\n";
	int i=1;
	for (const auto& p : discordantPairs) {
		cout <<i<< ". (" << movies[p.first - 1] << ", " << movies[p.second - 1] << ")\n";
		i++;
	}

	double similarityPercent = double(concordantPairs) / totalPairs * 100;
	double dissimilarityPercent = double(inversions) / totalPairs * 100;

	cout << "\n\nSimilarity Percentage: " << similarityPercent << "%";
	cout << "\nDissimilarity Percentage: " << dissimilarityPercent << "%";

	if (similarityPercent > 50.0) {
		cout << "\n\nConclusion: The rankings are similar.\n";
	} else {
		cout << "\n\nConclusion: The rankings are not similar.\n";
	}

	return tau;
}

int main() {
	vector<string> movies = {
		"The Shawshank Redemption", "The Dark Knight", "Inception", "Forrest Gump", "The Matrix"
	};

	int n = movies.size();
	vector<int> A(n), B(n);

	cout << "\nRanking the movies: \n";
	for (int i = 0; i < n; ++i) {
		cout << i + 1 << ". " << movies[i] << endl;
	}

	cout << "\nEnter rankings for Person A (1 to 5):\n";
	for (int i = 0; i < n; ++i) {
		cin >> A[i];
	}

	cout << "\nEnter rankings for Person B (1 to 5):\n";
	for (int i = 0; i < n; ++i) {
		cin >> B[i];
	}

	double tau = kendallTau(A, B, movies);

	cout << "\nKendall's Tau Rank Correlation Coefficient: " << tau << endl;

	return 0;
}
