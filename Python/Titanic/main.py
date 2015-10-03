import re
import pandas
from sklearn.feature_selection import SelectKBest, f_classif
import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
from sklearn import cross_validation
from sklearn.ensemble import RandomForestClassifier


class Titanic:
    def __init__(self):
        self.family_id_mapping_ = {}
        self.unic_names_ = set()
        self.titanic_ = None

    def get_title(self, name):
        title_search = re.search(' ([A-Za-z]+)\.', name)
        if title_search:
            return title_search.group(1)
        return ""

    def get_family_id(self, row):
        last_name = row["Name"].split(",")[0]
        family_id = "{0}{1}".format(last_name, row["FamilySize"])
        if family_id not in self.family_id_mapping_:
            if len(self.family_id_mapping_) == 0:
                current_id = 1
            else:
                current_id = len(self.family_id_mapping_) + 1
            self.family_id_mapping_[family_id] = current_id
        return self.family_id_mapping_[family_id]

    def init_dataset(self):
        self.titanic_ = pandas.read_csv("train.csv")
        self.titanic_["Age"] = self.titanic_["Age"].fillna(self.titanic_["Age"].median())
        self.titanic_["Fare"] = self.titanic_["Fare"].fillna(self.titanic_["Fare"].median())
        self.titanic_.loc[self.titanic_["Sex"] == "male", "Sex"] = 0
        self.titanic_.loc[self.titanic_["Sex"] == "female", "Sex"] = 1
        self.titanic_["Embarked"] = self.titanic_["Embarked"].fillna("S")

        self.titanic_.loc[self.titanic_["Embarked"] == "S", "Embarked"] = 0
        self.titanic_.loc[self.titanic_["Embarked"] == "C", "Embarked"] = 1
        self.titanic_.loc[self.titanic_["Embarked"] == "Q", "Embarked"] = 2

        self.titanic_["FamilySize"] = self.titanic_["SibSp"] + self.titanic_["Parch"]
        self.titanic_["NameLength"] = self.titanic_["Name"].apply(lambda x: len(x))
        self.unic_names_ = set((row["Name"].split(',')[0] for (i, row) in self.titanic_.iterrows()))
        self.family_id_mapping_ = {f_name: f_id for (f_id, f_name) in enumerate(self.unic_names_)}

        family_ids = self.titanic_.apply(self.get_family_id, axis=1)
        family_ids[self.titanic_["FamilySize"] < 3] = -1
        self.titanic_["FamilyId"] = family_ids
        titles = self.titanic_["Name"].apply(self.get_title)
        title_mapping = {"Mr": 1, "Miss": 2, "Mrs": 3, "Master": 4, "Dr": 5, "Rev": 6, "Major": 7, "Col": 7, "Mlle": 8, "Mme": 8, "Don": 9, "Lady": 10, "Countess": 10, "Jonkheer": 10, "Sir": 9, "Capt": 7, "Ms": 2}
        for k,v in title_mapping.items():
            titles[titles == k] = v

        self.titanic_["Title"] = titles

        predictors = ["Pclass", "Sex", "Age", "SibSp", "Parch", "Fare", "Embarked", "FamilySize", "Title", "FamilyId"]
        selector = SelectKBest(f_classif, k=4)
        selector.fit(self.titanic_[predictors], self.titanic_["Survived"])
        scores = -np.log10(selector.pvalues_)
        plt.bar(range(len(predictors)), scores)
        plt.xticks(range(len(predictors)), predictors, rotation='vertical')
        plt.show()
        predictors = [predictor for selected, predictor in zip(selector.get_support(), predictors) if selected]
        print(predictors)


def main():
    titanic = Titanic()
    titanic.init_dataset()
    #score = -np.log10(bestSelection.pvalues_)
    #plt.bar(range(len(predictors)), score)
    #plt.xticks(range(len(predictors)), predictors, rotation='vertical')
    #plt.show()


if  __name__ == '__main__':
    main()

__author__ = 'lisgein'
