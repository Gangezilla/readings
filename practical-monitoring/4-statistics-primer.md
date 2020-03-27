# Statistics Primer

Keeping lots of data opens up many new possibilities for problem detection through the use of statistics.

## Mean and average

Average is useful for determining what a dataset generally looks like without examining every single entry in the set.

A common use of averaging in time series is something called the *moving average*. This is where you calculate the average as new datapoints arrive and you smooth out a spiky graph.

## Median

Median is helpful when the average isn't going to be accurate, and it is the "middle" of the dataset. When dealing with datasets that skew heavily in one direction, the median is more representative than the mean.

## Seasonality

This is when your datapoints adopt a repeating pattern. If I know, based on previous data, that my servers handle roughly 100 requests/sec on a given weekday then I can assume that half or double that number is worth investigating. For workloads with a high degree of seasonality, you can make assumptions about the future. Beware, not all workloads have seasonality.

## Quantiles

Quantiles are a way of describing a specific point in a dataset.

First, you sort the data in ascending order, then the top n percent of values is removed. The next largest number is the nth percentile.

You can't average percentiles as you drop some amount of data.

## Standard Deviation

This is a method of describing how close or far values are from the mean. It will only work for a *normally distributed* dataset. Not-normal distributions are skewed, have multiple peaks

However, most data we'll use won't work within this framework soooooo generally don't worry about it.

Think about:

- Does it have a large skew in either direction?
- Are extreme outliers common?
- Are there upper/lower bounds?